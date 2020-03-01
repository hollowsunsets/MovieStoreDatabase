#ifndef TRANSACTIONCOMMAND_H
#define TRANSACTIONCOMMAND_H

#include "transaction.h"

// static, abstract Command performed on transactions
// a TransactionCommand can execute a particular type of Transaction,
// given a Transaction with the correct type/data
class TransactionCommand {
 public:
  // return the transaction type associated with this TransactionCommand 
  char get_transaction_type() const {return transaction_type;};
  virtual bool execute(const Transaction& transaction) = 0;
 protected:
  const static char transaction_type;
};

#endif // TRANSACTIONCOMMAND_H
