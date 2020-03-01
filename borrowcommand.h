#ifndef BORROWCOMMAND_H
#define BORROWCOMMAND_H

#include "transactioncommand.h"

// BorrowCommand executes Borrow transactions,
// decrementing stock for the specified Item
// and adding the transaction to the customer's history
class BorrowCommand : protected TransactionCommand {
 public:
  bool execute(const Transaction& transaction);
 protected:
  const static char transaction_type = 'B';
};

#endif // BORROWCOMMAND_H
