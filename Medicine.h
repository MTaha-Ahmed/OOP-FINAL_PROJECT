#ifndef MEDICINE_H
#define MEDICINE_H

#include "Product.h"
#include <string>

class Medicine : public Product {
private:
    std::string expiryDate;
public:
    Medicine(int id, std::string name, double price, std::string expiry);
    void getDetails() const override;
    std::string getExpiry() const;
    void setExpiryDate(std::string newExpiry);
};
#endif