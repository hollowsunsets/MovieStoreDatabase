#ifndef HISTORYCOMMAND_H
#define HISTORYCOMMAND_H

#include "transactioncommand.h"

// HistoryCommand executes History transactions,
// displaying the transaction history for a specified customer
class HistoryCommand : protected TransactionCommand {
 public:
  bool execute(const Transaction& transaction);
 protected:
  const static char transaction_type = 'H';
};

#endif // HISTORYCOMMAND_H
