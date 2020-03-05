#ifndef CUSTOMERTABLE_H
#define CUSTOMERTABLE_H

#include "customer.h"

// table of Customer data for a Store
// operations are constant amortized time
class CustomerTable {
 public:
  CustomerTable();
  ~CustomerTable();

  // add a new customer record to the table
  void insert(const Customer &c);
  // remove a customer from the table
  void remove(int id);
  // record a customer's Transaction, by customer id
  void record_transaction(int id, const Transaction& transaction);
  // retrieve the customer data, by customer id
  const Customer& retrieve(int id) const;

  // display table entries
  void display_table() const;

 protected:
  // calculate hash location for a given id (>=0 & <=9999)
  //(MOVE THIS TO IMPLEMENTATION:)
  // using modified (16-bit) Pearson's Method
  int hash(int id) const;

 private:
  const static int INITIAL_SIZE = 256;
  Customer * customers[INITIAL_SIZE];
};

#endif // CUSTOMERTABLE_H
