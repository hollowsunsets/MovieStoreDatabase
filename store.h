// ---------------------------- Store.h ---------------------------------
// Isabel Giang, Yttria Aniseia
// CSS 343 C: Data Structures and Algorithms II
// Creation Date: February 23, 2020
// Date of Last Modification: 
// Assignment 4: Movie Store Database
// ----------------------------------------------------------------------------
// Purpose: Declaring the functions of the Store class
// ----------------------------------------------------------------------------

#ifndef STORE_H
#define STORE_H

#include "customertable.h"
#include "item.h"
#include <map>
#include <iostream>
#include <string>

class Store {
    static const int INVENTORY_SIZE = '~' - 'A';
public:
    Store();
    ~Store();
    // Builds inventory from given input stream
    bool read_inventory(const std::string& filename);
    // Builds customer table from given input stream
    bool read_customers(const std::string& filename);
    // Builds transaction list from given input stream
    bool read_commands(const std::string& filename);
    // Add a customer to the customer table
    void add_customer(Customer&);
    // Adds an item to the inventory
    void add_item(Item*);

    // Executes the given transaction
    bool execute_transaction(Transaction*);
    // Records that the given item is borrowed
    bool borrow_item(char typecode, const std::string&);
    // Records that the given item has been returned
    bool return_item(char typecode, const std::string&);
    // Prints the inventory of the Store
    void display_inventory();
    // Prints the transaction history of all Customers of the Store
    bool display_history();
    // Prints the transaction history on one Customer specified
    bool display_history(int id);
private:
    Item* get_item(char typecode, const std::string& key);
    CustomerTable* customer_table;
    std::map<std::string, Item*> inventory[INVENTORY_SIZE];
};

#endif // STORE_H
