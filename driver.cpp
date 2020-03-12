#include <assert.h>
#include <iostream>
#include <sstream>
#include "customer.h"
#include "store.h"

using namespace std;

void test_customer() {
    cout << "Testing Customer class..." << endl;
    cout << "\tTesting Customer constructor..." << endl;
    Customer c(1001, "Reimu", "Hakurei");
    Customer c1(1002, "Bobby", "Joe");
    ostringstream s1;
    ostringstream s2;
    s1 << c;
    cout << "\t\t" << c;
    assert(s1.str() == "Customer 1001, Reimu Hakurei history: []\n");
    s1.str("");

    bool exception_thrown = false;
    try {
        Customer badC(10000, "Jane", "Doe");
    } catch (...) {
        cout << "\t\tException thrown when creating customer with id out of range" << endl;
        exception_thrown = true;
    }
    assert(exception_thrown);

    cout << "\tTesting Customer copy constructor..." << endl;
    Customer c2(c1);
    s1 << c1;
    s2 << c2;
    cout << "\t\t" << c1;
    cout << "\t\t" << c2;
    assert(s1.str() == s2.str());
    s1.str("");
    s2.str("");

    cout << "\tTesting Customer record_transaction..." << endl;
    Transaction t('B', 1001, 'D', 'C', "9 1938 Katherine Hepburn");
    Transaction t2('R', 1001, 'D', 'C', "9 1938 Katherine Hepburn");
    assert(c.record_transaction(t));
    assert(c.record_transaction((t2)));
    assert(!c1.record_transaction(t));

    cout << "\tTesting Customer display_history..." << endl;
    s1 << c;
    cout << "\t\t" << c;
    assert(s1.str() == "Customer 1001, Reimu Hakurei history: "
                       "[ B 1001 D C 9 1938 Katherine Hepburn | "
                       "R 1001 D C 9 1938 Katherine Hepburn ]\n");

    cout << "Customer tests pass!" << endl;
}

void test_store() {
    cout << "Testing Store class..." << endl;
    Store s;
    cout << "Testing Store.read_customers()..." << endl;
    assert(s.read_customers("data/data4customers.txt"));
}

int main() {
    test_customer();
    test_store();
}
