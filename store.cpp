// ---------------------------- Store.cpp ---------------------------------
// Isabel Giang, Yttria Aniseia
// CSS 343 C: Data Structures and Algorithms II
// Creation Date: February 23, 2020
// Date of Last Modification: 
// Assignment 4: Movie Store Database
// ----------------------------------------------------------------------------
// Purpose: Defining the functions of the Store class
// ----------------------------------------------------------------------------

#include "store.h"
#include "customer.h"
#include "customertable.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

Store::Store() {
    customer_table = CustomerTable();
}

Store::~Store() {
}

bool Store::read_inventory(const std::string& filename) {

}

/* read_customers: Builds a CustomerTable from the contents of
 *                 the given text file.
 *                 Ex: 1111 Mickey Mouse
 * Preconditions: The given filename corresponds to a file.
 * Postconditions: CustomerTable is populated with dynamically allocated Customers.
 */
bool Store::read_customers(const std::string& filename) {
    std::ifstream infile(filename.c_str());
    if (!infile) {
        std::cout << "File " << filename << " could not be opened." << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(infile, line)) {
        std::cout << line << std::endl;
        std::istringstream stream(line);
        int customer_id;
        std::string first_name, last_name;
        stream >> customer_id >> first_name >> last_name;
        customer_table.insert(Customer(customer_id, first_name, last_name));
    }
    customer_table.display_table();
    return true;
}

bool Store::read_commands(const std::string& filename) {

}

void Store::add_customer(Customer &) {

}

void Store::add_item(Item *) {

}

bool Store::execute_transaction(Transaction &) {

}

bool Store::borrow_item(const std::string &) {

}

bool Store::return_item(const std::string &) {

}

void Store::display_inventory() {
}

void Store::display_history() {

}