// --------------------------- TransactionFactory.h ---------------------------------
// Isabel Giang, Yttria Aniseia
// CSS 343 C: Data Structures and Algorithms II
// Creation Date: February 24, 2020
// Date of Last Modification:
// Assignment 4: Movie Store Database
// ----------------------------------------------------------------------------
// Purpose: Defining the functions of the TransactionFactory class
// ----------------------------------------------------------------------------

#include "transactionfactory.h"
#include <sstream>
#include <string>


/* create_transaction
 * Preconditions:
 * Postconditions:
 */
Transaction* TransactionFactory::create_transaction(const std::string& s) {
    char typecode = s.substr(0, s.find(" ")).c_str()[0];
    std::string transaction_data = s.substr(s.find(" ") + 1);
    switch (typecode) {
        case 'B':
            return BorrowTransaction::create_transaction(transaction_data);
        case 'R':
            return ReturnTransaction::create_transaction(transaction_data);
        case 'H':
            return HistoryTransaction::create_transaction(transaction_data);
        case 'I':
            return InventoryTransaction::create_transaction();
        default:
            std::cerr << "Invalid Transaction Code: " << typecode << std::endl;
            return NULL;
    }
}

