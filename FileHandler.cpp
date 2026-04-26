#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

void FileHandler::saveTransactionHistory(const string& log) {
    try {
        ofstream outFile("transactions.txt", ios::app);
        if (!outFile) {
            throw string("File error: Could not open transactions.txt");
        }
        outFile << log << endl;
        outFile.close();
        cout << "Saved to file successfully." << endl;
    } catch (const string e) {
        cerr << e << endl;
    }
}