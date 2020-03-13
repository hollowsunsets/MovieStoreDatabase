#include "item.h"

Item::Item() {
    stock = 0;
};

Item::Item(int stock) {
    this->stock = stock;
}

// getter for type
// preconditions: none
// postconditions: none
char Item::get_typecode() const {
    return typecode;
}


bool operator<(const Item &m, const Item &o) {
    return m.get_typecode() < o.get_typecode()
                              || m.get_key() < o.get_key();
}
bool operator>(const Item &m, const Item &o) {
    return m.get_typecode() > o.get_typecode()
                              || m.get_key() > o.get_key();
}
bool operator==(const Item &m, const Item &o) {
    return m.get_typecode() == o.get_typecode()
                              && m.get_key() == o.get_key();
}

// if d is a positive integer,
// add d to the item's stock and return true
// otherwise, do not perform the operation and return false
bool Item::add_stock(int d) {
    if (d <= 0) {
        return false;
    }
    stock += d;
    return true;
}

// if d is a positive integer and <= stock,
// subtract d from the item's stock and return true
// otherwise, do not perform the operation and return false
bool Item::remove_stock(int d) {
    if (d <= 0 || d > stock) {
        return false;
    }
    stock -= d;
    return true;
}

