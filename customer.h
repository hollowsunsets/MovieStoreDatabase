

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <stack>
#include <iostream>
#include "transaction.h"


class Customer {
 public:
  friend ostream& operator<<(ostream& out, Customer c);
  
  Customer(int id, const string &first_name, const string &last_name);

  void record_transaction(Transaction t);
  bool borrow_item(Item* item);
  bool return_item(Item* item)
  void display_history() const;
  
 private:
  int id;
  string first_name;
  string last_name;
  std::stack<Transaction> transaction_history;
}

#endif // CUSTOMER_H
