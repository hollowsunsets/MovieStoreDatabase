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

  // Redirect standard output to stringstream
  std::stringstream history;
  std::streambuf* old_buffer = std::cout.rdbuf(history.rdbuf());
  c.display_history();

  // Reset standard output to previous buffer
  std::cout.rdbuf(old_buffer);
  out << history.str();
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


/* record_transaction: Add a transaction to the customer's transaction history
 * Preconditions: The given Transaction must have the same ID as this Customer.
 * Postconditions: Transaction history should print in reverse chronological order.
 */
bool Customer::record_transaction(const Transaction& t) {
  if (t.customer_id != this->id) {
    return false;
  }
  transaction_history.push_back(t);
  return true;
}

/* display_history: Prints the Customer's history in reverse chronological order.
 * Preconditions: N/A
 * Postconditions: N/A
 */
void Customer::display_history() const {
  std::deque<Transaction>::const_iterator it = transaction_history.begin();
  std::cout << " history: [";

  if (it != transaction_history.end()) std::cout << " " << *it++ << " ";
  while (it != transaction_history.end())
      std::cout << "| " << *it++ << " ";
  std::cout << "]"  << std::endl;
}

