#ifndef TRANSACTION_H
#define TRANSACTION_H


#include "Product.h"
#include "Customer.h"

#include <string>

class Transaction {
    friend void generateSalesReport();
public:
    static int totalTransactions; 
    std::string processSale(Customer* customer, Product* product,int qty);
};
#endif