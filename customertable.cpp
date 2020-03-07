#include "customertable.h"

CustomerTable::CustomerTable() {
  customers = new Customer*[INITIAL_SIZE];
}

CustomerTable::~CustomerTable() {
  // is this correct i have no idea
  delete[] customers;
}

void CustomerTable::insert(const Customer &c) {
  // TODO: need some way to do table resize
  // which i totally forgot about; might need fullness member too
  
  int idx = hash(c.get_id());
  // quadratic probing
  int m = 0;
  while (customers[(idx + m) % size] != NULL) {
    if (m) m *= 2; else m = 1;
  }
  customers[(idx + m) % size] = new Customer(c);
}

void CustomerTable::remove(int id) {
  int idx = hash(id);
  // quadratic probing again; note searching for a match instead of empty
  int m = 0;
  while (customers[(idx + m) % size]->get_id() != id) {
    if (m) m *= 2; else m = 1;
  }
  customers[(idx + m) % size] = NULL;
}

void CustomerTable::record_transaction(int id, const Transaction &transaction) {
  // search for id, then call record_transaction on it
  // use retrieve()
}

// should this be returning a pointer?
// if add transaction uses it, can't be const, at least
const Customer& CustomerTable::retrieve(int id) const {
  // search for id, and return it
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
