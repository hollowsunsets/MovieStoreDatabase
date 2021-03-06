// --------------------------- Customer.cpp ---------------------------------
// Isabel Giang, Yttria Aniseia
// CSS 343 C: Data Structures and Algorithms II
// Creation Date: February 24, 2020
// Date of Last Modification:
// Assignment 4: Movie Store Database
// ----------------------------------------------------------------------------
// Purpose: Defining the functions of the Customer class.
// ----------------------------------------------------------------------------

#include "customer.h"
#include <stdexcept>
#include <sstream>
#include <iostream>

/* operator<<: Prints a string representation of this Customer.
 *             Customer 1001, Reimu Hakurei history: [ B 1001 D F Happily Never After, 2001 ]
 * Preconditions: N/A
 * Postconditions: N/A
 */
std::ostream& operator<<(std::ostream& out, const Customer& c) {
  out << "Customer " << c.id << ", " << c.first_name << " " << c.last_name;
  c.display_history(out);
  return out;
}

/* Constructor for Customer.
 * Preconditions: 0000 < id < 9999
 * Postconditions: N/A
 */
Customer::Customer(int id,
                   const std::string first_name, const std::string last_name) {
  if (id < 0 || id > 9999) {
    throw std::invalid_argument("Cannot create Customer with id < 0 or id > 9999.");
  }
  this->id = id;
  this->first_name = first_name;
  this->last_name = last_name;
}

/* Copy constructor 
 * Preconditions: 0000 < c.id < 9999
 * Postconditions: N/A
 */ 
Customer::Customer(const Customer &c) {
  this->id = c.id;
  this->first_name = c.first_name;
  this->last_name = c.last_name;
}

Customer::~Customer() {
    while (!transaction_history.empty()) {
        transaction_history.pop_front();
    }
}

// get customer's id
// preconditions: none
// postconditions: none
int Customer::get_id() const {
  return id;
}

/* record_transaction: Add a transaction to the customer's transaction history
 * Preconditions: The given Transaction must have the same ID as this Customer.
 * Postconditions: Transaction history should print in reverse chronological order.
 */
bool Customer::record_transaction(Transaction* t) {
  if (t->customer_id != this->id) {
    return false;
  }
  transaction_history.push_back(t);
  return true;
}

// the customer only cares about recording that the customer has a copy
// it does not take care of e.g. stock handling, that happens elsewhere
// preconditions: item_key is matches a key provided by get_key()
// postconditions: item_key is added to the borrows list for this customer
bool Customer::borrow_item(const std::string& item_key) {
    borrows.push_back(item_key);
    return true;
}

// the customer only cares about removing the item
// from the customer's borrows list, it does not take care of e.g. stock handling
// preconditions: item_key matches a key provided by get_key()
// postconditions: if true: borrows list contains one less instance of item_key
//                 if false: no effect, item was not borrowed
bool Customer::return_item(const std::string& item_key) {
    for (std::vector<std::string>::iterator it = borrows.begin();
         it != borrows.end(); ++it) {
        if (*it == item_key) {
            borrows.erase(it);
            return true;
        }
    }
    // item was not borrowed
    return false;
}

/* display_history: Prints the Customer's history in reverse chronological order.
 * Preconditions: N/A
 * Postconditions: N/A
 */

void Customer::display_history(std::ostream& out) const {
  std::deque<Transaction*>::const_iterator it = transaction_history.begin();
  out << " history: [";
  if (it != transaction_history.end()) {
      out << "\n";
  }
  while (it != transaction_history.end()) {
      out << "\t" << (*it++) << "\n";
  }
  out << "]";
}

