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
#include <sstream>

// Constructor: Constructs a new CustomerTable.
// Preconditions:  N/A
// Postconditions: Dynamically allocates an array pointer to hold
// a size of 2 as the default lowest size.
CustomerTable::CustomerTable() {
    size = INITIAL_SIZE;
    elements = 0;
    customer_table = new Customer*[INITIAL_SIZE];
    for (int i = 0; i < INITIAL_SIZE; i++) {
        customer_table[i] = NULL;
    }
}

// Destructor: Deallocates the contents of the CustomerTable.
// Preconditions: N/A
// Postconditions: N/A
//
CustomerTable::~CustomerTable() {
    this->clear();
}

// insert: Inserts a new Customer into the Customer Table.
// Preconditions: Customer c != NULL
// Postconditions: New Customer is dynamically allocated.
//
void CustomerTable::insert(const Customer& c) {
    int load_factor = (elements + 1) / size;
    if (load_factor > 0.5) {
        // Resize the hash table by replacing it with a new table
        this->elements = 0;
        this->customer_table = get_resized_table();
    }
    this->insert_to_table(c, this->customer_table);
}

// insert_to_table: Helper method that inserts the given Customer to the
//                  given table.
// Preconditions:   Customer != NULL, customers != NULL
// Postcondition: N/A

void CustomerTable::insert_to_table(const Customer &c, Customer** customers) {
    ++elements;
    int index = hash(c.get_id());
    // quadratic probing
    int jumps = 0, m = 0;

    int cluster_index = (index + m) & (size - 1);

    while (cluster_index >= 0 && cluster_index < size && customers[cluster_index] != NULL &&
           customers[cluster_index]->get_id() != c.get_id()) {
        m = probe_size(++jumps);
        cluster_index = (index + m) & (size - 1);
    }
    delete customers[cluster_index];
    customers[cluster_index] = new Customer(c);
}


// remove: Removes the Customer that corresponds with the given id
// Preconditions: Given id must exist within the customer table.
// Postconditions: Cluster of Customers with the same cluster
//                 as the removed Customer are rehashed.
//
bool CustomerTable::remove(int id) {
    this->retrieve(id);
    int index = hash(id);
    int jumps = 0, m = 0;
    int cluster_index = (index + m) & (size - 1);
    while (cluster_index >= 0 && cluster_index < size &&
           customer_table[cluster_index] != NULL &&
           customer_table[cluster_index]->get_id() != id) {
        m = probe_size(++jumps);
        cluster_index = (index + m) & (size - 1);
    }
    if (customer_table[cluster_index] == NULL) {
        return false;
    }
    delete customer_table[cluster_index];
    customer_table[cluster_index] = NULL;

    // Get next index of next element in cluster
    m = probe_size(++jumps);
    cluster_index = (index + m) & (size - 1);

    // Rehash the keys in the same cluster
    while (customer_table[cluster_index] != NULL) {
        Customer* customer_to_rehash = customer_table[cluster_index];
        customer_table[cluster_index] = NULL;
        --elements;
        this->insert(*customer_to_rehash);
        m = probe_size(++jumps);
        cluster_index = (index + m) & (size - 1);
    }
    --elements;
    return true;
}

// record_transaction: Records the given Transaction in the history of  
//		       the Customer that corresponds with the given ID.
// Precondition: ID must exist in the Customer Table.
// Postcondition: N/A
void CustomerTable::record_transaction(int id, Transaction* transaction) {
    Customer c = this->retrieve(id);
    c.record_transaction(transaction);
}

// retrieve: Retrieves the Customer that corresponds with the given
//           ID contained in the CustomerTable.
// Precondition: ID must exist in the Customer Table.
// Postcondition: N/A
Customer& CustomerTable::retrieve(int id) {
    int index = hash(id);
    int jumps = 0, m = 0;
    int cluster_index = (index + m) & (size - 1);

    while (cluster_index >= 0 && cluster_index < size &&
           customer_table[cluster_index] != NULL) {

        if (customer_table[cluster_index]->get_id() == id) {
            return *customer_table[cluster_index];
        }
        m = probe_size(++jumps);
        cluster_index = (index + m) & (size - 1);
    }
    std::stringstream error_message;
    throw std::invalid_argument(error_message.str());
}

// display_table: Prints an ASCII representation of the CustomerTable.
// Precondition:  N/A
// Postcondition: N/A
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

// hash: Hash function based on Pearson hashing to
//       yield 16 bits instead of the usual 8 bits.
//       Low entropy is expected in the high bits of the id.
// Preconditions:  Given id occupies only 16 bits.
// Postconditions: N/A
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
    return ((hash_hi << 8) | hash_lo) & (size - 1);
}

// get_resized_table: Helper function that returns a pointer to a table
//                    with a size with the next largest power of two.
// Precondition:      CustomerTable is initialized.
// Postcondition:     Base pointer is deallocated and replaced with new array.
Customer** CustomerTable::get_resized_table() {
    int old_size = size;
    size = size << 1;
    Customer** new_customer_table = new Customer*[size];
    for (int i = 0; i < size; i++) {
        new_customer_table[i] = NULL;
    }
    for (int i = 0; i < old_size; i++) {
        if (customer_table[i] != NULL) {
            this->insert_to_table(*customer_table[i], new_customer_table);
        }
        delete customer_table[i];
        customer_table[i] = NULL;
    }
    delete[] customer_table;
    return new_customer_table;
}

// clear: Helper function that deletes the contents of the CustomerTable.
// Precondition: CustomerTable is dynamically allocated
// Postcondition: CustomerTable is deallocated

void CustomerTable::clear() {
    for (int i = 0; i < size; i++) {
        if (customer_table[i] != NULL) {
            delete customer_table[i];
            customer_table[i] = NULL;
        }
    }
    delete[] customer_table;
}


// probe_size: Probing function that computes the size of the jump
//             based on the given number of jumps.
//             P(K, i) = (i^2 + i) / 2 for table with sizes of powers-of-two
// Precondition: jumps >= 1
// Postcondition: N/A
//
int CustomerTable::probe_size(int jumps) {
    return ((jumps * jumps) + jumps) / 2;
}
