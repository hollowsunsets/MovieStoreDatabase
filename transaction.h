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

// glorified struct
// represents data needed to carry out a transaction
// this object can easily be passed to TransactionCommand
// for execution
//
// TODO: may be converted to a properly encapsulated class
// or back to a struct on implementation
class Transaction {
    friend std::ostream& operator<<(std::ostream& out, const Transaction& t) {
        out << t.transaction_type << " " << t.customer_id << " " << t.item_type << " ";
        out << t.item_typecode << " " << t.item_data;
        return out;
    }
public:
    // the unique char identifying the type of transaction
    // valid values correspond to derived TransactionCommands
    char transaction_type;

    // id of target customer, if present, or 0
    unsigned short customer_id;

    // for transactions with item data, the item group code
    // e.g. DVD, CD, VCR Player, ...
    // must be in [A..~] (ASCII 65-126)
    char item_type;

    // for transactions with item data, the item subgroup code
    // e.g. genre, manufacturer
    // must be in [A..~] (ASCII 65-126)
    char item_typecode;

    // remaining unparsed item fields
    // to be handled by appropriate Item subclass
    // on construction
    std::string item_data;

    // Constructor
    Transaction(char trans_type, unsigned short id, char item_type, char typecode, std::string data) {
        this->transaction_type = trans_type;
        this->customer_id = id;
        this->item_type = item_type;
        this->item_typecode = typecode;
        this->item_data = data;
    }
};

#endif // TRANSACTION_H
