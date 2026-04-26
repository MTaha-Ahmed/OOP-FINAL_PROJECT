#ifndef INVENTORY_H
#define INVENTORY_H

#include "Product.h"
#include <string>

class Inventory {
private:
    Product** products;
    int capacity;
    int count;

public:
    static int totalProducts;

    Inventory(int cap);
    ~Inventory();

    void addProduct(Product* p);
    void displayInventory() const;
    void searchByName(std::string name) const;
    Product* getProductById(int id) const;
    bool removeProduct(int id); 
};

#endif