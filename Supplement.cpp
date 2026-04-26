#include "Supplement.h"
#include <iostream>

using namespace std;

Supplement::Supplement(int id, string name, double price, string vitamin) 
    : Product(id, name, price),vitaminType(vitamin) {}

void Supplement::getDetails() const {
    cout << "[Supplement] " << *this << " | Vitamin: " << vitaminType << " | Quantity: "<< quantity <<endl;
}
void Supplement::setVitaminType(string newVitamin) { vitaminType = newVitamin; }
string Supplement::getVitaminType() {return vitaminType;}