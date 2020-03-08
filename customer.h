// --------------------------- Customer.h ---------------------------------
// Isabel Giang, Yttria Aniseia
// CSS 343 C: Data Structures and Algorithms II
// Creation Date: February 24, 2020
// Date of Last Modification:
// Assignment 4: Movie Store Database
// ----------------------------------------------------------------------------
// Purpose: Declaring the functions of the Customer class.
// ----------------------------------------------------------------------------

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <stack>
#include <iostream>
#include <string>
#include "transaction.h"
#include "item.h"

class Customer {
 public:
  friend std::ostream& operator<<(std::ostream& out, const Customer& c);
  
  Customer(int id, const std::string first_name, const std::string last_name);
  Customer(const Customer& c);
  bool record_transaction(const Transaction& t);
  void display_history(std::ostream& out = std::cout) const;
  
 private:
  int id;
  std::string first_name;
  std::string last_name;
  std::deque<Transaction> transaction_history;
};

#endif // CUSTOMER_H
