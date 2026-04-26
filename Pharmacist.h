#ifndef PHARMACIST_H
#define PHARMACIST_H

#include "Person.h"
#include <string>

class Pharmacist : public Person {
private:
    std::string shift;
    std::string password;
public:
    Pharmacist(int id, std::string name, std::string shift,std::string password);
    void display() const override;
    bool verifyPassword(std::string inputPass) const;
};

#endif