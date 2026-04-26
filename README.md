# 🏥 Pharmacy Management System

## 📌 Project Description
The **Pharmacy Management System** is a robust, console-based C++ application designed to streamline the daily operations of a pharmacy. Built heavily on Object-Oriented Programming (OOP) principles, the software provides a secure and efficient way to manage medicinal inventory, process point-of-sale transactions, authenticate staff members, and generate persistent daily sales reports. 

Key technical features include **inheritance** (separating standard medicines and supplements), **encapsulation** (secure password handling via getter/verifier methods), strategic **friend functions/classes** for optimized and safe data access, **file handling** (`<fstream>`) for persistent transaction logging, and the use of **dynamic casting** (`dynamic_cast`) for runtime type identification during inventory updates. The UI is enhanced using ANSI escape codes for color-coordinated terminal output, and all user input is guarded by a centralized, robust input validation function to prevent infinite loops and program crashes.

## 👥 Group Members
* **25K-0650** M.Taha Ahmed
* **25K-0649** Mubashir Nadeem
* **25K-0701** Jasir Sheikh

## ⚙️ Core Use Cases
Here are the core use cases the system handles:
1. **Secure Staff Authentication:** Pharmacists must log in using a unique ID and a securely verified password. Administrators can register new staff, which utilizes a real-time `while` loop for password confirmation and validation.
2. **Dynamic Inventory Updating:** Users can search for a product by ID and enter a continuous sub-menu to update its name, price, and category-specific details (e.g., Expiry Date for Medicines, Vitamin Type for Supplements) without returning to the main menu.
3. **Add & Restock Inventory:** Users can add new standard medicines and vitamin supplements. If a product ID already exists, the system intelligently prompts the user to restock (update the quantity) rather than duplicating the item.
4. **Process Point-of-Sale Transactions:** Pharmacists can process purchases by searching for an item ID, inputting a purchase quantity, validating stock availability, and automatically deducting the sold amount. The `Transaction` class acts as a friend to access required customer details safely.
5. **Persistent Transaction Logging:** Every completed sale automatically generates a receipt and appends the transaction data (Customer, Item, Quantity, Total) to an external text file (`transactions.txt`).
6. **Generate Daily Sales Reports:** A designated `friend` function bypasses standard access to securely read the aggregated `totalTransactions` and reads directly from the `transactions.txt` file to generate a color-coded End-of-Day Sales Report in the terminal.

## 💻 How to Compile the Project
To compile the project, you must compile all the source (`.cpp`) files together. Open your terminal or command prompt, navigate to the project directory, and run the following command:

```bash
# Compile all C++ files into an executable named 'pharmacy'
g++ *.cpp -o pharmacy
🚀 How to Run the Project
Once compilation is complete, run the executable based on your operating system:

For Windows:

Bash
pharmacy.exe
For macOS / Linux:

Bash
./pharmacy
📖 How to Use the System
Initial Login: Upon launching, select Option 1 to log in. Use the default Admin credentials to gain access:

ID: 901

Password: admin123

Navigation: Use the numeric menu to navigate the system. Type the number corresponding to your desired action and press Enter. If a character is typed by mistake, the system will safely catch it and prompt you to try again.

Managing Inventory: Before processing sales, use the Add Product options to build initial stock. You can edit any existing stock using the Update Product Details option.

Processing Sales: Use the Process Sale option for a customer transaction. You will need the ID of the product and the desired quantity. The system will alert you if stock is insufficient and calculate the final bill.

Viewing Reports: At the end of your session, use the Sales Report option to view a formatted, color-coded summary of all transactions processed that day.

⚠️ Assumptions & Limitations
Terminal Color Support: The system utilizes ANSI escape codes (\033[...m) to render colored text and text formatting (Bold, Underline). The terminal/console running the program must support ANSI formatting to display correctly (Standard in macOS/Linux, and modern Windows Terminals).

Volatile Inventory Memory: While transactions are saved persistently to transactions.txt, the inventory state and newly added staff members are stored in system memory. Restarting the program will reset the inventory and staff list to their default hardcoded states.

Staff Capacity: The system assumes a maximum capacity of 10 staff members logged into the system array at any given time.

File Permissions: The system assumes the program has read/write permissions in its current directory to automatically create and update transactions.txt.