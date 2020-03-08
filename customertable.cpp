// --------------------------- CustomerTable.cpp ---------------------------------
// Isabel Giang, Yttria Aniseia
// CSS 343 C: Data Structures and Algorithms II
// Creation Date: February 23, 2020
// Date of Last Modification: 
// Assignment 4: Movie Store Database
// ----------------------------------------------------------------------------
// Purpose: Defining the functions of the CustomerTable class
// ----------------------------------------------------------------------------

#include "customertable.h"

CustomerTable::CustomerTable() {
  customers = new Customer*[INITIAL_SIZE];
}

CustomerTable::~CustomerTable() {
  // is this correct i have no idea
  delete[] customers;
}

// Quadratic probing, where h(k, i) = (h'(k) + c_1 * i + c_2 * i^2)
void CustomerTable::insert(const Customer &c) {
  // TODO: need some way to do table resize
  // which i totally forgot about; might need fullness member too
  load_factor = ++elements / size;
  if (load_factor > 0.5) {
      // Resize the hash table
  }
  int index = hash(c.get_id());
  // quadratic probing
  int jumps = 0, m = 0;
  while (customers[(index + jumps + (jumps * jumps)) % size] != NULL) {
      ++jumps;
      m = jumps * jumps;
  }
  customers[(index + m) % size] = new Customer(c);
  load_factor = (++elements / size);
}


void CustomerTable::remove(int id) {
  int index = hash(id);
  // quadratic probing again; note searching for a match instead of empty
  int jumps = 0, m = 0;
  while (customers[(index + m) % size]->get_id() != id) {
    ++jumps;
    m = jumps * jumps;
  }
  customers[(index + m) % size] = NULL;
}

void CustomerTable::record_transaction(int id, const Transaction &transaction) {
  // search for id, then call record_transaction on it
  // use retrieve()
}

// should this be returning a pointer?
// if add transaction uses it, can't be const, at least
Customer& CustomerTable::retrieve(int id) const {
  // search for id, and return it
  
}
Customer& CustomerTable::operator[](int id) {
  
}


void CustomerTable::display_table() const {
  // just loop through and print indexes + value
}

// Pearson hashing modified to yield up to 16 bits
// we expect low entropy in the high bits of id
int CustomerTable::hash(int id) const {
  // initialize high and low parts
  // considering using uint_8 here
  int hash_lo = shuffle[id & 0x00FF];
  int hash_hi = shuffle[(id & 0xFF00) >> 8];
  // shuffle round 1 based on xor (low against low)
  hash_lo = shuffle[hash_lo ^ (id & 0x00FF)];
  // shuffle round 2 based on xor (shuffled low against high)
  hash_lo = shuffle[hash_lo ^ (id & 0xFF00) >> 8];

  // high against low/high
  hash_hi = shuffle[hash_hi ^ (id & 0x00FF)];
  hash_hi = shuffle[hash_hi ^ (id & 0xFF00) >> 8];

  // combine to get 16 bits, then modulo size  
  return ((hash_hi << 8) | hash_lo) % size;
}

void CustomerTable::resize(int capacity) {
    
}
