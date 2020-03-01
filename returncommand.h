#ifndef RETURNCOMMAND_H
#define RETURNCOMMAND_H

#include "transactioncommand.h"

// ReturnCommand executes Return transactions,
// incrementing stock for the specified Item
// and adding the transaction to the customer's history
class ReturnCommand : protected TransactionCommand {
 public:
  bool execute(const Transaction& transaction);
 protected:
  const static char transaction_type = 'R';
};

#endif // RETURNCOMMAND_H
