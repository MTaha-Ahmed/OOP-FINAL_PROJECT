#include "Pharmacist.h"
#include <iostream>

using namespace std;

Pharmacist::Pharmacist(int id, string name, string shift,string password) 
    : Person(id, name), shift(shift),password(password) {}

void Pharmacist::display() const {
    cout << "[Pharmacist] ID: " << id << ", Name: " << name 
         << ", Shift: " << shift << endl;
}
bool Pharmacist::verifyPassword(std::string inputPass) const {
        return password == inputPass;
    }