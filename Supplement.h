#ifndef SUPPLEMENT_H
#define SUPPLEMENT_H

#include "Product.h"
#include <string>

class Supplement : public Product {
private:
    std::string vitaminType;
public:
    Supplement(int id, std::string name, double price, std::string vitamin);
    void getDetails() const override;
    void setVitaminType(std::string newVitamin);
    std::string getVitaminType();
};
#endif