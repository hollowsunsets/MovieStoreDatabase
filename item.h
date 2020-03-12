#ifndef ITEM_H
#define ITEM_H

#include <string>

// abstract Item class
// represents products that might be carried by a Store inventory
// and can be sorted into an inventory
// see also ItemFactory
class Item {
 public:
  // we also expect Items to implement constructor using input line format
  Item();
  Item(int stock);
    
  char get_typecode() const;

  // add the quantity d to the item's stock
  bool add_stock(int d);

  // remove quantity d from the item's stock
  bool remove_stock(int d);

  // get comparison key 
  virtual std::string get_key() const = 0;

  // comparison operators
  // for sorting into Inventory for fast lookup
  virtual bool operator<(const Item&);
  virtual bool operator>(const Item&);
  virtual bool operator==(const Item&);
  
 protected:
  // amount of the item in stock
  int stock;

  // item subgroup type
  // e.g. movie genre, device manufacturer
  // must be in [A..~] (ASCII 65-126)
  const static char typecode;

  // derived classes have additional data fields
};

#endif // ITEM_H
