#include "customertable.h"
#include "item.h"
#include <map>
#include <string>

#ifndef STORE_H
#define
class Store {
public:
    Store();
    ~Store();
private:
    CustomerTable customer_table;
    std::map<std::string, Item*> inventory;
};

#endif // STORE_H
