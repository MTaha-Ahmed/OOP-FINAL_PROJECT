#include "Medicine.h"
#include <iostream>

using namespace std;

Medicine::Medicine(int id, string name, double price, string expiry) 
    : Product(id, name, price), expiryDate(expiry) {}

void Medicine::getDetails() const {
    cout << "[Medicine] " << *this << " | Expiry: " << expiryDate << " | Quantity: "<< quantity <<endl;
};//*this is the actual object so <<*this calls the overloaded operator <<product to output the details 
void Medicine::setExpiryDate(string newExpiry) { expiryDate = newExpiry; }
string Medicine::getExpiry() const { 
    return expiryDate; 
}