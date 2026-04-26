#include "Inventory.h"
#include <iostream>

using namespace std;

const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";

int Inventory::totalProducts = 0;

Inventory::Inventory(int cap) : capacity(cap), count(0) {
    products = new Product*[capacity];
}

Inventory::~Inventory() {
    for (int i = 0; i < count; i++) {
        delete products[i];
    }
    delete[] products;
}

void Inventory::addProduct(Product* p) {
    if (count < capacity) {
        products[count++] = p;
        totalProducts++;
        cout << GREEN << "Product added successfully!" << RESET << endl;
    } else {
        cout << RED << "Inventory full! Cannot add more products." << RESET << endl;
        delete p; 
    }
}

void Inventory::displayInventory() const {
    if (count == 0) {
        cout << RED << "Inventory is empty." << RESET << endl;
        return;
    }
    for (int i = 0; i < count; i++) {
        products[i]->getDetails();//overriding. getDetails() will be called according to the pointer type
    }
}

void Inventory::searchByName(string name) const {
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (products[i]->getName() == name) {
            products[i]->getDetails();//overriding
            found = true;
        }
    }
    if (!found) {
        cout << RED <<  "Product not found." << RESET << endl;
    }
}


bool Inventory::removeProduct(int id) {
    for (int i = 0; i < count; i++) {
        if (products[i]->getId() == id) {
            delete products[i]; 

            for (int j = i; j < count - 1; j++) {
                products[j] = products[j + 1];
            }
            
            count--; 
            totalProducts--; 
            
            return true; 
        }
    }
    return false; 
}
Product* Inventory::getProductById(int id) const {
    for (int i = 0; i < count; i++) {
        if (products[i]->getId() == id) {
            return products[i]; 
        }
    }
    return nullptr; 
}