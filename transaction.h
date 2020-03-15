// --------------------------- Transaction.h ---------------------------------
// Isabel Giang, Yttria Aniseia
// CSS 343 C: Data Structures and Algorithms II
// Creation Date: February 24, 2020
// Date of Last Modification:
// Assignment 4: Movie Store Database
// ----------------------------------------------------------------------------
// Purpose: Declaring and defining the functions of the Transaction class
// ----------------------------------------------------------------------------

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
#include <vector>

// glorified struct
// represents data needed to carry out a transaction
// this object can easily be passed to TransactionCommand
// for execution
//
class Transaction {
    friend std::ostream& operator<<(std::ostream& out, Transaction* t) {
        out << t->transaction_type;
        if (t->transaction_type != 'I'){
            out << " " << t->customer_id << " " << t->data;
        }
        return out;
    }
public:
    Transaction() {};
    Transaction(char transaction_type, int customer_id, std::string data) {
        this->transaction_type  = transaction_type;
        this->customer_id = customer_id;
        this->data = data;
    }
    char get_transaction_type() const { return transaction_type;  };
    int customer_id;
    char transaction_type;
    std::string data;
};

/* Example: B 1234 D C 9 1938 Katherine Hepburn
 *
 *
 */
class BorrowTransaction : public Transaction {
public:
    BorrowTransaction(int character_id,
                     std::string data) : Transaction('B', character_id, data) {};
    static BorrowTransaction* create_transaction(const std::string& s);
protected:
    int character_id;
    std::string data;
};

/* Example: R 1234 D C 9 1938 Katherine Hepburn
 *
 *
 */
class ReturnTransaction : public Transaction {
public:
    ReturnTransaction(int character_id, std::string data) : Transaction('R', character_id, data) {};
    static ReturnTransaction* create_transaction(const std::string& s);

protected:
    int character_id;
    std::string data;
};

/* Example: H 1234
 *
 *
 */
class HistoryTransaction : public Transaction {
public:
    HistoryTransaction(int character_id) : Transaction('H', character_id, "") { }
    static HistoryTransaction* create_transaction(const std::string& s);
protected:
    int character_id;
};

/* Example: I, no other fields
 *
 *
 */
class InventoryTransaction : public Transaction {
public:
    InventoryTransaction() : Transaction('I', 0, "") {};
    static InventoryTransaction* create_transaction();
};

std::vector<std::string> &split(const std::string &s, char delim,  std::vector<std::string>& elems);

#endif // TRANSACTION_H
