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
    size = INITIAL_SIZE;
    elements = 0;
    load_factor = elements / size;
    customer_table = new Customer*[INITIAL_SIZE];
}

CustomerTable::~CustomerTable() {
    for (int i = 0; i < size; i++) {
        if (customer_table[i] != NULL) {
            delete customer_table[i];
        }
    }
    delete[] customer_table;
}

void CustomerTable::insert(const Customer& c) {
    this->insert_to_table(c, this->customer_table);
}

// Private helper method
// Doing this so we don't have to redefine insert in resize.
// Maybe better way to do this? Tried defining customer_table as default paramater
// in insert() but you cannot pass non static class members as parameters
// Quadratic probing, where h(k, i) = (h'(k) + c_1 * i + c_2 * i^2)
void CustomerTable::insert_to_table(const Customer &c, Customer** customers) {
    load_factor = ++elements / size;
    if (load_factor > 0.5) {
        resize();
        // Resize the hash table
    }
    int index = hash(c.get_id());
    // quadratic probing
    int jumps = 0, m = 0;
    while (customers[(index + m) % size] != NULL &&
           customers[(index + m) % size]->get_id() != c.get_id()) {
        ++jumps;
        m = jumps * jumps;
    }
    customers[(index + m) % size] = new Customer(c);
    std::cout << "Just inserted: " << customers[(index + m) % size] << " ";
    std::cout << *customers[(index + m) % size] << std::endl;
    this->display_table();
    load_factor = (++elements / size);
}

void CustomerTable::remove(int id) {
    int index = hash(id);
    // quadratic probing again; note searching for a match instead of empty
    int jumps = 0, m = 0;
    while (customer_table[(index + m) % size]->get_id() != id) {
        ++jumps;
        m = jumps * jumps;
    }
    customer_table[(index + m) % size] = NULL;
    elements--;
}

void CustomerTable::record_transaction(int id, const Transaction &transaction) {
    // search for id, then call record_transaction on it
    // use retrieve()
    Customer* c = this->retrieve(id);
    // TODO: Assuming retrieve returns NULL if it doesn't find anything.
    // Probably need to fix this.
    if (c != NULL) {
        c->record_transaction(transaction);
    }
}

// should this be returning a pointer?
// if add transaction uses it, can't be const, at least
Customer* CustomerTable::retrieve(int id) const {
    int index = hash(id);
    int jumps = 0, m = 0;

    while (customer_table[(index + m) % size]->get_id() != id) {
        ++jumps;
        m = jumps * jumps;
    }
    // TODO: What if the key doesn't exist in the hash table?
    return customer_table[(index + m) % size];
}

void CustomerTable::display_table() const {
    std::cout << "{ " << 0 << " : ";
    if (customer_table[0]) {
        std::cout << "\"" << *customer_table[0] << "\"";
    } else {
        std::cout << "\"" << 0 << "\"";
    }
    for (int i = 1; i < size; i++) {
        std::cout << ", " << i << " : ";
        if (customer_table[i]) {
            std::cout << "\"" << *customer_table[i] << "\"";
        } else {
            std::cout << "\"" << 0 << "\"";
        }
    }
    std::cout << "}" << std::endl;
}

// Pearson hashing modified to yield up to 16 bits
// we expect low entropy in the high bits of id
int CustomerTable::hash(int id) const {
    // initialize high and low parts
    // considering using uint_8 here
    int hash_lo = SHUFFLE[id & 0x00FF];
    int hash_hi = SHUFFLE[(id & 0xFF00) >> 8];
    // shuffle round 1 based on xor (low against low)
    hash_lo = SHUFFLE[hash_lo ^ (id & 0x00FF)];
    // shuffle round 2 based on xor (shuffled low against high)
    hash_lo = SHUFFLE[hash_lo ^ (id & 0xFF00) >> 8];

    // high against low/high
    hash_hi = SHUFFLE[hash_hi ^ (id & 0x00FF)];
    hash_hi = SHUFFLE[hash_hi ^ (id & 0xFF00) >> 8];

    // combine to get 16 bits, then modulo size
    return ((hash_hi << 8) | hash_lo) % size;
}

void CustomerTable::resize() {
    Customer** new_customer_table = new Customer*[size << 1];
    this->elements = 0;
    for (int i = 0; i < size; i++) {
        if (customer_table[i] != NULL) {
            this->insert_to_table(*customer_table[i], new_customer_table);
            // TODO: Not sure if this even works
            delete customer_table[i];
        }
    }
    delete[] customer_table;
    this->customer_table = new_customer_table;
    this->size = size << 1;
}
