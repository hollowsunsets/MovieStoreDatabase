#ifndef ITEM_H
#define ITEM_H

// abstract Item class
// represents products that might be carried by a Store inventory
// and can be sorted into an inventory
// see also ItemFactory
class Item {
 public:
  Item();
  
  char get_typecode() const;

  // add the quantity d to the item's stock
  //(MOVE THIS TO .cpp:)
  // if d is a positive integer and <= stock,
  // subtract d from the item's stock and return true
  // otherwise, do not perform the operation and return false
  bool add_stock(int d);

  // remove quantity d from the item's stock
  //(MOVE THIS TO .cpp:)
  // if d is a positive integer and <= stock,
  // subtract d from the item's stock and return true
  // otherwise, do not perform the operation and return false
  bool remove_stock(int d);

  // comparison operators
  // for sorting into Inventory for fast lookup
  virtual bool operator<(const Item&) = 0;
  virtual bool operator>(const Item&) = 0;
  virtual bool operator==(const Item&) = 0;
  
 private:
  // amount of the item in stock
  int stock;
  // item group code, defined by classes of rentable items
  // e.g. DVD?, VCR Player 
  // may be unused
  const char groupcode;
  // item subgroup type
  // e.g. movie genre, device manufacturer
  // must be in [A..~] (ASCII 65-126)
  const char typecode;

  // derived classes have additional data fields
};

#endif // ITEM_H
