// --------------------------- TransactionFactory.h ---------------------------------
// Isabel Giang, Yttria Aniseia
// CSS 343 C: Data Structures and Algorithms II
// Creation Date: February 24, 2020
// Date of Last Modification:
// Assignment 4: Movie Store Database
// ----------------------------------------------------------------------------
// Purpose: Defining the functions of the TransactionFactory class
// ----------------------------------------------------------------------------


#ifndef TRANSACTION_FACTORY_H
#define TRANSACTION_FACTORY_H
#include "transaction.h"

class TransactionFactory {
public:
    TransactionFactory();
    static Transaction* create_transaction(const std::string& s);
};

#endif // TRANSACTION_FACTORY_H
