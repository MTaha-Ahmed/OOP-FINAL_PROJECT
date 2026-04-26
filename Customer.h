#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"
#include <string>

class Customer : public Person {
private:
    std::string contactNumber;
public:
    Customer(int id, std::string name, std::string contact);
    void display() const override;
    std::string getContactNo();
};

#endif