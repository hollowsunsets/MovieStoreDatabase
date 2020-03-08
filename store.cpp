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

Store::Store() {

}

Store::~Store() {

}

bool Store::read_inventory(const std::string& filename) {

}

bool Store::read_customers(const std::string& filename) {
    std::ifstream infile(filename.c_str());
    if (!infile) {
        std::cout << "File " << filename << " could not be opened." << std::endl;
        return false;
    }
    std::string line;
    // Only print for now because no CustomerTable implementation yet
    while (std::getline(infile, line)) {
        std::cout << line << std::endl;
    }
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