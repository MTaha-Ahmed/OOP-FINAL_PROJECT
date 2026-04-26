#include "Product.h"

using namespace std;

Product::Product(int id, string name, double price) {
    this->id = id;
    this->name = name;
    this->price = price;
}

Product::~Product() {}

int Product::getId() const { return id; }
string Product::getName() const { return name; }
double Product::getPrice() const { return price; }

bool Product::operator==(const Product& other) const {
    return this->id == other.id;
}

ostream& operator<<(ostream& os, const Product& p) {
    os << "ID: " << p.id << " | Name: " << p.name << " | Price: $" << p.price;
    return os;
}
void Product::setQuantity(int q) { quantity = q; }
int Product::getQuantity() const { return quantity; }
void Product::decreaseQuantity() { 
        if (quantity > 0) {
            quantity--; 
        }
    }
void Product::setName(string newName) { name = newName; }
void Product::setPrice(double newPrice) { price = newPrice; }