#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>

class Product {
protected:
    int id;
    int quantity=1;
    std::string name;
    double price;
public:
    Product(int id, std::string name, double price);
    virtual ~Product();

    int getId() const;
    std::string getName() const;
    double getPrice() const;

    virtual void getDetails() const = 0; 

    bool operator==(const Product& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Product& p);
    void setQuantity(int q) ;
    int getQuantity() const ;
    void decreaseQuantity();
    void setName(std::string newName);
    void setPrice(double newPrice);
};
#endif