#ifndef STORE_H
#define STORE_H

#include "customertable.h"
#include "item.h"
#include <map>
#include <iostream>
#include <string>

class Store {
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
    bool execute_transaction(Transaction&);
    // Records that the given item is borrowed
    bool borrow_item(const std::string&);
    // Records that the given item has been returned
    bool return_item(const std::string&);
    // Prints the inventory of the Store
    void display_inventory();
    // Prints the transaction history of all Customers of the Store
    void display_history();
private:
  std::map<std::string, Item*> inventory[127 - 65];
  CustomerTable customer_table;
};

#endif // STORE_H
