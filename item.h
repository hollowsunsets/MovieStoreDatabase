// ---------------------------item.h ---------------------------------
// Isabel Giang, Yttria Aniseia
// CSS 343 C: Data Structures and Algorithms II
// Creation Date: February 23, 2020
// Date of Last Modification: 
// Assignment 4: Movie Store Database
// ----------------------------------------------------------------------------
// Purpose: Defining the functions of the Item class
// ----------------------------------------------------------------------------


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
  virtual ~Item();

  virtual void print(std::ostream& out) const = 0;
    
  // get comparison key 
  virtual std::string get_key() const = 0;
    
  virtual char get_typecode() const = 0;

  // add the quantity d to the item's stock
  bool add_stock(int d);

  // remove quantity d from the item's stock
  bool remove_stock(int d);
    
  // comparison operators
  // for sorting into Inventory for fast lookup
  friend bool operator<(const Item&, const Item&);
  friend bool operator>(const Item&, const Item&);
  friend bool operator==(const Item&, const Item&);
  
 protected:
  // amount of the item in stock
  int stock;
    
  // derived classes have additional data fields
};

#endif // ITEM_H
