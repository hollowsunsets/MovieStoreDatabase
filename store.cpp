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
#include "item.h"
#include "itemfactory.h"
#include "customer.h"
#include "customertable.h"
#include "itemfactory.h"
#include "transaction.h"
#include "transactionfactory.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Store::Store() {
    customer_table = new CustomerTable();
}

Store::~Store() {
    delete customer_table;
}


bool Store::read_inventory(const std::string& filename) {
    std::ifstream infile(filename.c_str());
    if (!infile) {
        std::cout << "File " << filename << " could not be opened." << std::endl;
        return false;
    }

    std::string line;
    Item* item;
    while (std::getline(infile, line)) {
        item = ItemFactory::create_item(line);
        if (item == NULL) {
            std::cout << "Ignoring invalid item: " << line << std::endl;
        } else {
            add_item(item);
        }
    }

    infile.close();
    return true;
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
        Customer c = Customer(customer_id, first_name, last_name);
        customer_table->insert(c);
    }
    customer_table->display_table();

    infile.close();
    return true;
}

bool Store::read_commands(const std::string& filename) {
    std::ifstream infile(filename.c_str());
    if (!infile) {
        std::cout << "File " << filename << " could not be opened." << std::endl;
        return false;
    }
    bool valid_transactions = true;
    std::string line;
    while (std::getline(infile, line)) {
        Transaction* new_transaction = TransactionFactory::create_transaction(line);
        if (new_transaction != NULL) {
            execute_transaction(new_transaction);
            delete new_transaction;
        } else {
            valid_transactions = false;
        }
    }
    infile.close();
    return valid_transactions;
}

void Store::add_customer(Customer& customer) {
    customer_table->insert(customer);
}

void Store::add_item(Item* i) {
    if (i == NULL) {
        return;
    }
    inventory[i->get_typecode() - 'A'][i->get_key()] = i;
}

Item* Store::get_item(char typecode, const std::string& key) {
    std::map<std::string,Item*>::iterator itemq;
    itemq = inventory[typecode - 'A'].find(key);
    if (itemq != inventory[typecode - 'A'].end()) {
        return itemq->second;
    }
    return NULL;
}


bool Store::execute_transaction(Transaction* ) {

}

bool Store::borrow_item(const std::string &) {
    
}

bool Store::return_item(const std::string &) {

}

void Store::display_inventory() {
    // this should really retrieve a list of item types from the factory
    
    for (std::map<std::string,Item*>::iterator it = inventory['F' - 'A'].begin();
         it != inventory['F' - 'A'].end();
         ++it) {
        it->second->print(std::cout);
        std::cout << std::endl;
    }
    
    for (std::map<std::string,Item*>::iterator it = inventory['D' - 'A'].begin();
         it != inventory['D' - 'A'].end();
         ++it) {
        it->second->print(std::cout);
        std::cout << std::endl;
    }

    for (std::map<std::string,Item*>::iterator it = inventory['C' - 'A'].begin();
         it != inventory['C' - 'A'].end();
         ++it) {
        it->second->print(std::cout);
        std::cout << std::endl;
    }
}

void Store::display_history() {
    customer_table->display_histories();
}
