#include "transaction.h"
#include <string>
#include <sstream>
#include <vector>

BorrowTransaction* BorrowTransaction::create_transaction(const std::string &s) {
    std::vector<std::string> tokens;
    split(s, ' ', tokens);
    int customer_id;
    std::istringstream(tokens[0]) >> customer_id;
    std::stringstream data_stream;
    data_stream << tokens[1];
    for (size_t i = 2; i < tokens.size(); ++i) {
        data_stream << " " << tokens[i];
    }
    return new BorrowTransaction(customer_id, data_stream.str());
}

ReturnTransaction* ReturnTransaction::create_transaction(const std::string &s) {
    std::vector<std::string> tokens;
    split(s, ' ', tokens);
    int customer_id;
    std::istringstream(tokens[0]) >> customer_id;
    std::stringstream data_stream;
    data_stream << tokens[1];
    for (size_t i = 2; i < tokens.size(); ++i) {
        data_stream << " " << tokens[i];
    }
    return new ReturnTransaction(customer_id, data_stream.str());
}

HistoryTransaction* HistoryTransaction::create_transaction(const std::string &s) {
    std::istringstream stream(s);
    int customer_id;
    std::string data;
    stream >> customer_id >> data;
    return new HistoryTransaction(customer_id);
}

InventoryTransaction* InventoryTransaction::create_transaction() {
    return new InventoryTransaction();
}

std::vector<std::string>& split(const std::string &s, char delim,
                                std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}