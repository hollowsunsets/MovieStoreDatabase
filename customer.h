#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <stack>
#include <iostream>
#include <string>
#include "transaction.h"
#include "item.h"

class Customer {
 public:
  friend std::ostream& operator<<(std::ostream& out, Customer c);
  
  Customer(int id, const std::string first_name, const std::string last_name);

  void record_transaction(const Transaction& t);
  void display_history() const;
  
 private:
  int id;
  std::string first_name;
  std::string last_name;
  std::deque<Transaction> transaction_history;
};

#endif // CUSTOMER_H
