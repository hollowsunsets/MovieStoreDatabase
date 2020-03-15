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
#include <vector>
#include "transaction.h"
#include "item.h"

class Customer {
 public:
  friend std::ostream& operator<<(std::ostream& out, const Customer& c);
  
  Customer(int id, const std::string first_name, const std::string last_name);
  Customer(const Customer& c);
  ~Customer();

  // record a transaction to the customer's history 
  bool record_transaction(Transaction* t);
  // add an item specifier to the customer's borrows list
  bool borrow_item(const std::string& item_key);
  // remove an item from the customer's borrows list,
  // returning FALSE if the item was not borrowed 
  bool return_item(const std::string& item_key);
  void display_history(std::ostream& out = std::cout) const;
  int get_id() const;

 private:
  int id;
  std::string first_name;
  std::string last_name;
  std::vector<std::string> borrows;
  std::deque<Transaction*> transaction_history;
};

#endif // CUSTOMER_H
