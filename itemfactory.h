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

};

#endif // ITEMFACTORY_H
