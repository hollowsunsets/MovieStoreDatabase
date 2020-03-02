#include "customertable.h"
#include "item.h"
#include <map>
#include <iostream>
#include <string>

#ifndef STORE_H
#define
class Store {
public:
    Store();
    ~Store();
    // Builds inventory from given input stream
    bool read_inventory(std::ifstream&);
    // Builds customer table from given input stream
    bool read_customer(std::ifstream&);
    // Builds transaction list from given input stream
    bool read_commands(std::ifstream&);
    // Add a customer to the customer table
    void add_customer(Customer&);
    // Adds an item to the inventory
    void add_item(Item*);

    // Executes the given transaction
    bool execute_transaction(Transaction&);
    // Records that the given item is borrowed
    bool borrow_item(const string&);
    // Records that the given item has been returned
    bool return_item(const string&);
    // Prints the inventory of the Store
    void display_inventory();
    // Prints the transaction history of all Customers of the Store
    void display_history();
private:
    CustomerTable customer_table;
    std::map<std::string, Item*> inventory;
};

#endif // STORE_H
