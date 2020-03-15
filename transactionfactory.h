#ifndef TRANSACTION_FACTORY_H
#define TRANSACTION_FACTORY_H
#include "transaction.h"

class TransactionFactory {
public:
    TransactionFactory();
    static Transaction* create_transaction(const std::string& s);
};

#endif // TRANSACTION_FACTORY_H
