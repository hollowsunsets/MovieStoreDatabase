// Customer Class
// 2020-03-04
#include "customer.h"
#include <stdexcept>

// output operator overload
// writes header specifying customer, then history of transactions
// Customer 1001, Reimu Hakurei history:
//  B 1001 D F Happily Never After, 2001
std::ostream& operator<<(std::ostream& out, Customer c) {
  out << "Customer " << c.id << ", " << c.first_name;
  out << " " << c.last_name << " history:" << std::endl;
  
  return out;
}

// explicit fields constructor
// preconditions: 0000 < id < 9999
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
 * Preconditions: N/A
 * Postconditions: N/A
 */ 
Customer::Customer(const Customer &c) {
  this->id = c.id;
  this->first_name = c.first_name;
  this->last_name = c.last_name;
}

// add a transaction to the customer's transaction history
// preconditions: T should have the same customer ID
// postconditions: t present at end of customer's history
bool Customer::record_transaction(const Transaction& t) {
  if (t.customer_id != this->id) {
    return false;
  }
  transaction_history.push_back(t);
  return true;
}


// display customer's history directly to stdout
void Customer::display_history() const {
  std::deque<int>::iterator it;

}

