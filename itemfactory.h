// --------------------------- ItemFactory.cpp ---------------------------------
// Isabel Giang, Yttria Aniseia
// CSS 343 C: Data Structures and Algorithms II
// Creation Date: February 23, 2020
// Date of Last Modification: 
// Assignment 4: Movie Store Database
// ----------------------------------------------------------------------------
// Purpose: Declaring the functions of the ItemFactory class
// ----------------------------------------------------------------------------
#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "item.h"
#include "movie.h"
#include <iostream>

// creates Items from lines in Inventory
class ItemFactory {
 public:
    ItemFactory();  

    // extract a line directly from input stream,
    // and return a pointer to the new Item or NULL if invalid
    static Item* create_item(std::istream& stream);
    // return a pointer to Item specified by s or NULL if invalid
    static Item* create_item(const std::string& s);

    static std::string item_data_to_key(const std::string& data);
    
};

#endif // ITEMFACTORY_H
