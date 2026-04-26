#include <iostream>
#include <string>
#include <fstream>
#include "Customer.h"
#include "Pharmacist.h"
#include "Medicine.h"
#include "Supplement.h"
#include "Inventory.h"
#include "Transaction.h"
#include "FileHandler.h"

using namespace std;

const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string CYAN = "\033[36m";
const string BLUE = "\033[34m";
const string YELLOW = "\033[33m";
const string BOLD  = "\033[1m";
const string UNDERLINE = "\033[4m";
const string MAGENTA = "\033[35m";
const string INVERSE = "\033[7m";

void generateSalesReport() {
    cout << CYAN << BOLD << "\n=====================================" << RESET << endl;
    cout << INVERSE << BLUE << BOLD << "        SALES REPORT      " << RESET << endl;
    cout << CYAN << BOLD << "=====================================" << RESET << endl;
    if(Transaction::totalTransactions==0){
        cout << RED << BOLD << "No sales were made today." << RESET << endl;
        return;
    }
    cout << YELLOW << "Total Transactions this session: " 
         << GREEN << BOLD << Transaction::totalTransactions << RESET << endl;
    
    cout << MAGENTA << UNDERLINE << "\n--- Detailed Transaction Log ---" << RESET << endl;

    ifstream inFile("transactions.txt");

    if (!inFile) {
        cout << RED << BOLD << "No transaction history found (transactions.txt does not exist or is empty)." << RESET << endl;
    } else {
        string line;
        while (getline(inFile, line)) {
            cout << CYAN << line << RESET << endl;
        }
        
        inFile.close(); 
    }
    
    cout << CYAN << BOLD << "=====================================" << RESET << endl;
}

void pressEnterToContinue() {
    cout << BOLD  << "\nPress Enter to continue..." << RESET;
    cin.get();
}

bool handleInputError(string errorMessage) {
    if (cin.fail()) {
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        cout << RED << BOLD << "Error: " << RESET << RED << errorMessage << RESET << endl;
        
        pressEnterToContinue();
        return true; 
    }
    return false; 
}

int main() {
    Pharmacist* staff[10]; 
    int staffCount = 0;
    staff[staffCount++] = new Pharmacist(901, "Dr. Bob", "Morning Shift", "admin123");
    Inventory myInventory(100);
    Transaction currentTransaction;
    Pharmacist* loggedInUser = nullptr; 
    int choice = 0;

    do {
        cout << BOLD << CYAN << "\n=========================================" << RESET << endl;
        cout << BOLD << CYAN << INVERSE << "       PHARMACY MANAGEMENT SYSTEM        " << RESET << endl;
        cout << BOLD << CYAN << "========================================="  << RESET << endl;
        
        if (loggedInUser != nullptr) {
            cout << "Logged in as: " << GREEN << BOLD << loggedInUser->getName() << RESET << endl;
        } else {
            cout << "Logged in as:" << YELLOW << " NONE (Please login)" << RESET << endl;
        }
        
        cout << "Total Products: " << BOLD << Inventory::totalProducts << RESET << " | Total Sales: " << BOLD << Transaction::totalTransactions << RESET << endl;
        cout << "-----------------------------------------" << endl;
        cout << "1. Login" << endl;
        cout << "2. Logout" << endl;
        cout << "3. Add a new Pharmacist" << endl;
        cout << "4. Add a new Medicine" << endl;
        cout << "5. Add a new Supplement" << endl;
        cout << "6. Update Product Details" << endl;
        cout << "7. Display full Inventory" << endl;
        cout << "8. Search for a Product" << endl;
        cout << "9. Process a Sale" << endl;
        cout << "10. Generate Sales Report" << endl;
        cout << "11. Exit Program" << endl;
        cout << "=========================================" << endl;
        cout << "Enter your choice (1-11): ";
        
        cin >> choice;
        if (handleInputError("Invalid input! Choice must be a number.")) {
                    continue; 
                }
        cin.ignore();

        if (choice >= 4 && choice <= 10 && loggedInUser == nullptr) {
            cout << "\n" << RED << BOLD << "Access Denied:" << RESET << RED <<" You must Login (Option 1) to use this feature!" << RESET << endl;
            pressEnterToContinue();
            continue; 
        }

        switch (choice) {
            case 1: {
                if (loggedInUser != nullptr) {
                    cout << "\n"<< RED << "You are already logged in as " << GREEN <<  loggedInUser->getName() << RED << ". Please logout first." << RESET << endl;
                    pressEnterToContinue();
                    break;
                }

                int loginId;
                cout << "\n" << MAGENTA << BOLD << UNDERLINE << "--- Login ---" << RESET << endl;
                cout << "Enter your Pharmacist ID: ";
                cin >> loginId;
                if (handleInputError("Invalid input! ID must be a number.")) {
                    break; 
                }
                cin.ignore(1000,'\n');

                Pharmacist* tempUser = nullptr;
                for (int i = 0; i < staffCount; i++) {
                    if (staff[i]->getId() == loginId) {
                        tempUser = staff[i];
                        break;
                    }
                }
                if (tempUser == nullptr) {
                    cout << RED << BOLD << "Error:" << RESET << RED << " Pharmacist ID not found. Access Denied." << RESET << endl;
                    pressEnterToContinue();
                    break;
                }
                string loginPass;
                cout << "Enter Password: ";
                getline(cin, loginPass);

                if (tempUser->verifyPassword(loginPass)) {
                    loggedInUser = tempUser; 
                    cout << GREEN << "Login Successful! Welcome, " << BOLD << loggedInUser->getName() << "!" << RESET << endl;
                } else {
                    cout <<  RED << BOLD << "Error: " << RESET << RED <<  " Incorrect Password. Access Denied." << RESET << endl;
                }
                pressEnterToContinue();
                break;
            }
            case 2: {
                if (loggedInUser == nullptr) {
                    cout << RED << "\nNobody is currently logged in." << RESET << endl;
                } else {
                    cout << "\nLogging out " << UNDERLINE <<  loggedInUser->getName() << RESET << "..." << endl;
                    loggedInUser = nullptr; // Clear the active user
                    cout << GREEN << "Logout successful." << RESET << endl;
                }
                pressEnterToContinue();
                break;
            }
            case 3: {
                if (staffCount >= 10) {
                    cout << "\n" << RED << BOLD << "Error:" << RESET << RED << " Maximum staff capacity (10) reached." << RESET << endl;
                    pressEnterToContinue();
                    break;
                }

                int newId;
                string newName, newShift;

                cout << "\n" << MAGENTA << BOLD << UNDERLINE <<  "--- Add New Pharmacist ---" << RESET << endl;
                cout << "Enter New Pharmacist ID: ";
                cin >> newId;
                if (handleInputError("Invalid input! ID must be a number.")) {
                    break; 
                }
                cin.ignore();

                bool idExists = false;
                for (int i = 0; i < staffCount; i++) {
                    if (staff[i]->getId() == newId) {
                        idExists = true;
                        break;
                    }
                }

                if (idExists) {
                    cout << RED << BOLD << "Error: " << RESET << RED << " Pharmacist ID " << newId << " already exists! Registration cancelled." << RESET << endl;
                    pressEnterToContinue();
                    break;
                }

                cout << "Enter Name: ";
                getline(cin, newName);

                cout << "Enter Shift (e.g., Morning, Night): ";
                getline(cin, newShift);

                string newPass, confirmPass;
                
                while (true) {
                    cout << "Create a Password: ";
                    getline(cin, newPass);
                    
                    cout << "Confirm Password: ";
                    getline(cin, confirmPass);
                    
                    if (newPass == confirmPass) {
                        break; 
                    } else {
                        cout << RED << BOLD <<  "\nError:" << RESET << RED << " Passwords do not match. Please try again." << RESET << endl;
                    }
                }

                staff[staffCount] = new Pharmacist(newId, newName, newShift,newPass);
                staffCount++;

                cout << GREEN  << BOLD <<  "Success!" << RESET << GREEN << " Pharmacist " << newName << " added to the system." << RESET << endl;
                pressEnterToContinue();
                break;
            }
            case 4: {
                int id,qty;
                string name, expiry;
                double price;

                cout << MAGENTA << BOLD << UNDERLINE << "\n--- Add New Medicine/Restock Medicine ---" << RESET << endl;
                cout << "Enter Product ID: ";
                cin >> id;
                if (handleInputError("Invalid input! ID must be a number.")) {
                    break; 
                }
                cin.ignore();

                Product* existingProduct = myInventory.getProductById(id);
                if (existingProduct != nullptr) {
                    int extraQty;
                    cout << "Product Found: " << existingProduct->getName() 
                         << " | Current Stock: " << existingProduct->getQuantity() << endl;
                    cout << "Enter quantity to ADD to existing stock: ";
                    cin >> extraQty;

                    if (cin.fail() || extraQty <= 0) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << RED << BOLD << "Error:" << RESET << RED << " Invalid quantity. Restock cancelled." << RESET << endl;
                    } else {
                        // Update the quantity 
                        existingProduct->setQuantity(existingProduct->getQuantity() + extraQty);
                        cout << GREEN << BOLD << "Success!" << RESET << GREEN << " Stock updated. New Quantity: " << BOLD << existingProduct->getQuantity() << RESET << endl;
                    }
                    
                    cin.ignore();
                    pressEnterToContinue();
                    break; 
                }
                cout << "Enter Name: ";
                getline(cin, name);

                cout << "Enter Price: $";
                cin >> price;
                if (handleInputError("Invalid input! Price must be a number.")) {
                    break; 
                }
                cin.ignore();

                cout << "Enter Expiry Date (YYYY-MM): ";
                getline(cin, expiry);

                cout << "Enter Quantity: "; 
                cin >> qty;
                if (handleInputError("Invalid input! Quantity must be a number.")) {
                    break; 
                }
                else if(qty<=0){
                    cout<< RED << "Quantity must be greater than zero.";
                    pressEnterToContinue();
                    break;
                }
                cin.ignore();
                Medicine* newMed = new Medicine(id, name, price, expiry);
                newMed->setQuantity(qty);
                myInventory.addProduct(newMed);
                pressEnterToContinue();
                break;
            }
            case 5: {
                int id,qty;
                string name, vitamin;
                double price;

                cout << MAGENTA << BOLD << UNDERLINE << "\n--- Add New Supplement/Restock Supplement ---" << RESET << endl;
                cout << "Enter Product ID: ";
                cin >> id;
                if (handleInputError("Invalid input! ID must be a number.")) {
                    break; 
                }
                cin.ignore();
                Product* existingProduct = myInventory.getProductById(id);

                if (existingProduct != nullptr) {
                    int extraQty;
                    cout << "Product Found: " << existingProduct->getName() 
                         << " | Current Stock: " << existingProduct->getQuantity() << endl;
                    cout << "Enter quantity to ADD to existing stock: ";
                    cin >> extraQty;

                    if (cin.fail() || extraQty <= 0) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << RED << BOLD << "Error:" << RESET << RED << " Invalid quantity. Restock cancelled." << RESET << endl;
                    } else {
                        // Update the quantity 
                        existingProduct->setQuantity(existingProduct->getQuantity() + extraQty);
                        cout << GREEN << BOLD <<  "Success!" << RESET << GREEN << " Stock updated. New Quantity: " << BOLD << existingProduct->getQuantity() << RESET <<  endl;
                    }
                    
                    cin.ignore();
                    pressEnterToContinue();
                    break; 
                }
                
                cout << "Enter Name: ";
                getline(cin, name);

                cout << "Enter Price: $";
                cin >> price;
                if (handleInputError("Invalid input! Price must be a number.")) {
                    break; 
                }
                cin.ignore();

                cout << "Enter Vitamin Type: ";
                getline(cin, vitamin);

                cout << "Enter Quantity: "; 
                cin >> qty;
                if (handleInputError("Invalid input! quantity must be a number.")) {
                    break; 
                }
                else if(qty<=0){
                    cout<< RED << "Quantity must be greater than zero.";
                    pressEnterToContinue();
                    break;
                }
                cin.ignore();
                Supplement* newSupp = new Supplement(id, name, price, vitamin);
                newSupp->setQuantity(qty);
                myInventory.addProduct(newSupp);
                pressEnterToContinue();
                break;
            }
            case 6: {
                int id;
                cout << CYAN << BOLD << "\n--- Update Product Details ---" << RESET << endl;
                cout << "Enter the ID of the product to update: ";
                cin >> id;
                if (handleInputError("Invalid input! ID must be a number.")) {
                    continue; 
                }
                cin.ignore(10000, '\n');
                Product* foundProduct = myInventory.getProductById(id);

                if (foundProduct == nullptr) {
                    cout << RED << BOLD << "Error: Product ID " << id << " not found in inventory." << RESET << endl;
                    pressEnterToContinue();
                    break;
                }
                bool keepUpdating = true; 
                while (keepUpdating) {
                    cout << "\nEditing Product: " << GREEN << BOLD << foundProduct->getName() << RESET << endl;
                    cout << "Current Price: $" << foundProduct->getPrice() << endl;
                    cout << "1. Update Name\n2. Update Price\n3. Update Category Details\n4. Done Editing\n";
                    cout << "What would you like to change? (1-4): ";
                    
                    int updateChoice;
                    cin >> updateChoice;

                    if (handleInputError("Invalid choice! Must be a number.")) {
                        continue; 
                    }
                    cin.ignore(10000, '\n');
                    if (updateChoice == 1) {
                        string newName;
                        cout << "Old Name: " << foundProduct->getName() << endl;
                        cout << "Enter new name: ";
                        getline(cin, newName);
                        foundProduct->setName(newName);
                        cout << GREEN << "Success! Name updated to: " << foundProduct->getName() << RESET << endl;

                    } else if (updateChoice == 2) {
                        double newPrice;
                        cout << "Old Price: $" << foundProduct->getPrice() << endl;
                        cout << "Enter new price: $";
                        cin >> newPrice;
                        
                        if (handleInputError("Invalid price format!")) continue;
                        
                        foundProduct->setPrice(newPrice);
                        cout << GREEN << "Success! Price updated to: $" << foundProduct->getPrice() << RESET << endl;

                    } else if (updateChoice == 3) {
                        Medicine* med = dynamic_cast<Medicine*>(foundProduct);
                        //casting into medicine type pointer,if it fails then it is not of medicine type
                        if (med != nullptr) {//if casted succesfully means it is a medicine
                            string newExpiry;
                            cout << "Current Expiry: " << med->getExpiry() << endl;
                            cout << "Enter new Expiry Date (YYYY-MM): ";
                            getline(cin, newExpiry);
                            med->setExpiryDate(newExpiry);
                            cout << GREEN << "Success! Expiry date updated." << RESET << endl;
                        } else {
                            Supplement* supp = dynamic_cast<Supplement*>(foundProduct);
                            if (supp != nullptr) {
                                string newVitamin;
                                cout << "Current Vitamin Type: " << supp->getVitaminType() << endl;
                                cout << "Enter new Vitamin Type: ";
                                getline(cin, newVitamin);
                                supp->setVitaminType(newVitamin);
                                cout << GREEN << "Success! Vitamin type updated." << RESET << endl;
                            }
                        }
                    } else if (updateChoice == 4) {
                        cout << CYAN << "Finished editing " << foundProduct->getName() << "." << RESET << endl;
                        keepUpdating = false; 
                        
                    } else {
                        cout << RED << "Invalid choice. Please select 1-4." << RESET << endl;
                    }
                } 
                pressEnterToContinue();
                break;
            }
            case 7: {
                cout << BLUE;
                myInventory.displayInventory();
                cout << RESET;
                pressEnterToContinue();
                break;
            }
            case 8: {
                string query;
                cout << "\nEnter the name of the product to search: ";
                getline(cin, query);
                myInventory.searchByName(query);
                pressEnterToContinue();
                break;
            }
            case 9: {
                int id;
                cout << MAGENTA << BOLD << UNDERLINE << "\n--- Process a Sale ---" << RESET << endl;
                cout << "Enter the ID of the product being sold: ";
                cin >> id;
                if (handleInputError("Invalid input! ID must be a number.")) {
                    break; 
                }
                cin.ignore();

                Product* foundProduct = myInventory.getProductById(id);

                if (foundProduct == nullptr) {
                    cout << RED << BOLD << "Error:" << RESET << RED << " Product ID " << BOLD << id << RESET << RED << " not found in inventory." << RESET << endl;
                    cout << RED << "Transaction cancelled." << RESET << endl;
                    pressEnterToContinue();
                    break;
                }
                int purchaseQty;
                cout << "Enter quantity to purchase: ";
                cin >> purchaseQty;
                if (handleInputError("Invalid input! quantity must be a number.")) {
                    break; 
                }
                cin.ignore();
                if (purchaseQty > foundProduct->getQuantity()) {
                    cout << RED << BOLD << "Error:" << RESET << RED << " Not enough stock! Only " << BOLD <<  foundProduct->getQuantity() << RESET << RED <<" remaining." << RESET << endl;
                    pressEnterToContinue();
                    break;
                }

                string name = foundProduct->getName();
                double price = foundProduct->getPrice();
        
                string custName, custContact;
                cout << "Enter Customer Name: ";
                getline(cin, custName);
                
                cout << "Enter Customer Contact Number: ";
                getline(cin, custContact);

                int dynamicCustomerID = Transaction::totalTransactions + 1;
                
                Customer* tempCustomer = new Customer(dynamicCustomerID, custName, custContact);
                Product* soldItem = new Medicine(id, name, price, "N/A");
                
                string transactionData = currentTransaction.processSale(tempCustomer, foundProduct, purchaseQty);
                transactionData= transactionData + " | Pharmacist Name: " + loggedInUser->getName();
                FileHandler::saveTransactionHistory(transactionData);
                
                foundProduct->setQuantity(foundProduct->getQuantity() - purchaseQty);
                cout << GREEN << "\nSale successful! Remaining stock for " << BOLD << foundProduct->getName() << ": " << foundProduct->getQuantity() << RESET << endl;

                if (foundProduct->getQuantity() == 0) {
                    cout << RED <<  "Stock is now empty. Automatically removing from database." << RESET << endl;
                    myInventory.removeProduct(id);
                }

                delete tempCustomer;
                delete soldItem; 
                
                pressEnterToContinue();
                break;
            }
            case 10:{
                generateSalesReport();
                pressEnterToContinue();
            }
            case 11: {
                cout << "\n" << BLUE << "Saving data and shutting down. Goodbye!" << RESET << endl;
                break; 
            }
            default: {
                cout << RED << BOLD << "Invalid choice." << RESET << RED << " Please select an option from 1 to 9." << RESET << endl;
                pressEnterToContinue();
                break;
            }
        }
    } while (choice != 11);

    for (int i = 0; i < staffCount; i++) {
        delete staff[i];
    }

    return 0;
}