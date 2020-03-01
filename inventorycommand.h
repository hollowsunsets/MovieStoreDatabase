#ifndef INVENTORYCOMMAND_H
#define INVENTORYCOMMAND_H

#include "transactioncommand.h"

// InventoryCommand executes Inventory transactions,
// displaying the inventory of the store
class InventoryCommand : protected TransactionCommand {
 public:
  // display Comedy entries, then Drama, then Classics
  bool execute(const Transaction& transaction);
 protected:
  const static char transaction_type = 'I';
};

#endif // INVENTORYCOMMAND_H
