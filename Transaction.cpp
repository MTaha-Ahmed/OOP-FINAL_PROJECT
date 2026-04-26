#include "Transaction.h"

#include <iostream>
#include <string> 

using namespace std;

int Transaction::totalTransactions = 0;

string Transaction::processSale(Customer* customer, Product* product, int qty) {
    totalTransactions++; 

    
    double totalCost = product->getPrice() * qty;

    // Receipt for the screen
    cout << "\n--- Receipt #" << totalTransactions << " ---" << endl;
    cout << "Customer ID: " << customer->getId() << endl; 
    cout << "Customer Name: " << customer->getName() << endl;
    cout<< "Customer Contact: "<< customer->getContactNo()<<endl;
    cout << "Product: " << product->getName() << " (x" << qty << ")" << endl;
    cout << "Total Cost: $" << totalCost << endl;
    cout << "---------------" << endl;

    string transactionData = "Transaction #" + to_string(totalTransactions) + 
                             " | Cust ID: " + to_string(customer->getId()) + 
                             " | Name: " + customer->getName() +
                             " | Contact: " + customer->getContactNo() +
                             " | Bought: " + to_string(qty) + "x " + product->getName() + 
                             " | Total: $" + to_string(totalCost);

    return transactionData;
}