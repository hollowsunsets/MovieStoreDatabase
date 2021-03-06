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
    for (std::map<std::string,Item*>::iterator it = inventory['F' - 'A'].begin();
         it != inventory['F' - 'A'].end();
         ++it) {
        delete it->second;
    }
    
    for (std::map<std::string,Item*>::iterator it = inventory['D' - 'A'].begin();
         it != inventory['D' - 'A'].end();
         ++it) {
        delete it->second;
    }

    for (std::map<std::string,Item*>::iterator it = inventory['C' - 'A'].begin();
         it != inventory['C' - 'A'].end();
         ++it) {
        delete it->second;
    }    
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
    // bool valid = true;
    std::string line;
    while (std::getline(infile, line)) {
        Transaction* transaction = TransactionFactory::create_transaction(line);
        if (transaction != NULL) {
            execute_transaction(transaction);
        } else {

        }
    }
    infile.close();
    return true;
}

// add a customer to the customer table
// preconditions: N/A
// postconditions: customer table's entry for customer.id == customer
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

bool Store::execute_transaction(Transaction* transaction) {
    std::string item_key;
    Customer* customer;
    switch (transaction->get_transaction_type()) {
    case 'I':
        display_inventory();
        delete transaction;
        return true;
    case 'H':
        if(!display_history(transaction->customer_id)) {
            std::cout << "Invalid transaction: " << transaction << std::endl;
            break;
        }
        delete transaction;
        return true;
    case 'B':
        item_key = ItemFactory::item_data_to_key(transaction->data);
        // std::cout << "borrow key: " << item_key << std::endl;
        customer = customer_table->retrieve(transaction->customer_id);
        if (!customer) {
            std::cout << "Invalid customer ID: " <<
                    transaction->customer_id << std::endl;
            break;
        }
        if(!borrow_item(transaction->data[2], item_key)) {
            std::cout << "Not in stock: " << transaction->data << std::endl;
            break;
        }
        customer->borrow_item(item_key);
        customer->record_transaction(transaction);
        return true;
    case 'R':
        item_key = ItemFactory::item_data_to_key(transaction->data);
        // std::cout << "return key: " << item_key << std::endl;
        customer = customer_table->retrieve(transaction->customer_id);
        if (!customer) {
            std::cout << "Invalid customer ID: " <<
                    transaction->customer_id << std::endl;
            break;
        }
        if (!customer->return_item(item_key)) {
            std::cout << "Item not borrowed: " << transaction->data << std::endl;
            break;
        }
        if (!return_item(transaction->data[2], item_key)) {
            std::cout << "Item cannot be returned: "
                      << transaction->data << std::endl;
            break;
        }
        customer->record_transaction(transaction);        
        return true;
    default:
        break;
    }
    delete transaction;
    return false;
}

bool Store::borrow_item(char typecode, const std::string& key) {
    Item* item = get_item(typecode, key);
    return item != NULL && item->remove_stock(1);
}

bool Store::return_item(char typecode, const std::string& key) {
    Item* item = get_item(typecode, key);
    // this should always be true in practice -- customer return acts as a guard
    return item != NULL && item->add_stock(1);    
}

// display Comedy movie, Drama movie, and Classic movie inventories
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

// display all customer histories
bool Store::display_history() {
    customer_table->display_histories();
    return true;
}

// display history of a given customer id
bool Store::display_history(int id) {
    Customer* c = customer_table->retrieve(id);
    if (c) {
        std::cout << *c << std::endl;
        return true;
    }

    std::cout << "Invalid customer ID: " << id;
    return false;
}
