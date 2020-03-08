// --------------------------- Customer.cpp ---------------------------------
// Isabel Giang, Yttria Aniseia
// CSS 343 C: Data Structures and Algorithms II
// Creation Date: February 23, 2020
// Date of Last Modification: 
// Assignment 4: Movie Store Database
// ----------------------------------------------------------------------------
// Purpose: Defining the functions of the Customer class
// ----------------------------------------------------------------------------


#include "customer.h"

// output operator overload
// writes header specifying customer, then history of transactions
// Customer 1001, Reimu Hakurei history:
//  B 1001 D F Happily Never After, 2001
std::ostream& operator<<(std::ostream& out, Customer c) {
  out << "Customer " << c.id << ", " << c.first_name;
  out << " " << c.last_name << " history:" << std::endl;
  
  // transaction iterator over customer's history
  std::deque<Transaction>::iterator t_it = c.transaction_history.begin();
  while (t_it != c.transaction_history.end()) {
    //out << *t_it++ << std::endl;
  }
  return out;
}

// explicit fields constructor
// preconditions: 0000 < id < 9999
Customer::Customer(int id,
                   const std::string first_name, const std::string last_name) {
  this->id = id;
  this->first_name = first_name;
  this->last_name = last_name;
}


/* Copy constructor for Customer
 * Preconditions: 0000 < id < 9999
 * Postconditions: N/A
*/
Customer::Customer(const Customer& c) {
  this->id = c.id;
  this->first_name = c.first_name;
  this->last_name = c.last_name;
}


// add a transaction to the customer's transaction history
// preconditions: none
// postconditions: t present at end of customer's history
void Customer::record_transaction(const Transaction& t) {
  transaction_history.push_back(t);
}

// get customer's id
// preconditions: none
// postconditions: none
int Customer::get_id() const {
  return id;
}

// display customer's history directly to stdout
// should this just be the history, and skip header,
// to differentiate from <<?
// preconditions: none
// postconditions: none
void Customer::display_history() const {
  std::cout << *this;
}

