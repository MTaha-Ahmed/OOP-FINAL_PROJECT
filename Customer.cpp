#include "Customer.h"
#include <iostream>

using namespace std;

Customer::Customer(int id, string name, string contact) 
    : Person(id, name), contactNumber(contact) {}

void Customer::display() const {
    cout << "[Customer] ID: " << id << ", Name: " << name 
         << ", Contact: " << contactNumber << endl;
}
string Customer::getContactNo(){
    return contactNumber;
}