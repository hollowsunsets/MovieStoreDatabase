#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

// glorified struct
// represents data needed to carry out a transaction
// this object can easily be passed to TransactionCommand
// for execution
//
// TODO: may be converted to a properly encapsulated class
// or back to a struct on implementation
class Transaction {
 public:
  // the unique char identifying the type of transaction
  // valid values correspond to derived TransactionCommands
  char transaction_type;

  // id of target customer, if present, or 0 
  unsigned short customer_id = 0;

  // for transactions with item data, the item group code
  // e.g. DVD, CD, VCR Player, ...
  // must be in [A..~] (ASCII 65-126)
  char item_type;

  // for transactions with item data, the item subgroup code
  // e.g. genre, manufacturer
  // must be in [A..~] (ASCII 65-126)
  char item_typecode;
  
  // remaining unparsed item fields
  // to be handled by appropriate Item subclass
  // on construction
  std::string item_data;
};

#endif // TRANSACTION_H
