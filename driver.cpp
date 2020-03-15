// --------------------------- driver.cpp ---------------------------------
// Isabel Giang, Yttria Aniseia
// CSS 343 C: Data Structures and Algorithms II
// Creation Date: February 23, 2020
// Date of Last Modification: 
// Assignment 4: Movie Store Database
// ----------------------------------------------------------------------------
// Purpose: Defining the functional requirements of the MovieStoreDatabase.
// ----------------------------------------------------------------------------

#include <assert.h>
#include <iostream>
#include <sstream>
#include <fstream>


#include "customer.h"
#include "item.h"
#include "movie.h"
#include "itemfactory.h"
#include "store.h"
#include "transaction.h"
#include "transactionfactory.h"

using namespace std;

void test_customer() {
    cout << "Testing Customer class..." << endl;
    cout << "\tTesting Customer constructor..." << endl;
    Customer c(1001, "Reimu", "Hakurei");
    Customer c1(1002, "Bobby", "Joe");
    ostringstream s1;
    ostringstream s2;
    s1 << c;
    cout << "\t\t" << c << endl;
    assert(s1.str() == "Customer 1001, Reimu Hakurei history: []");
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
    cout << "\t\t" << c1 << endl;
    cout << "\t\t" << c2 << endl;
    assert(s1.str() == s2.str());
    s1.str("");
    s2.str("");

    cout << "\tTesting Customer record_transaction..." << endl;
    Transaction* t = TransactionFactory::create_transaction("B 1001 D C 9 1938 Katherine Hepburn");
    Transaction* t2 = TransactionFactory::create_transaction("R 1001 D C 9 1938 Katherine Hepburn");
    assert(c.record_transaction(t));
    assert(c.record_transaction((t2)));
    assert(!c1.record_transaction(t));

    cout << "\tTesting Customer display_history..." << endl;
    s1 << c;
    cout << "\t\t" << c << endl;
    assert(s1.str() == "Customer 1001, Reimu Hakurei history: "
                       "[ B 1001 D C 9 1938 Katherine Hepburn | "
                       "R 1001 D C 9 1938 Katherine Hepburn ]");

    cout << "\tTesting Customer borrow and return..." << endl;
    //string format doesn't matter
    cout << "\t\tBorrowing Dichromatic Lotus Butterfly" << endl;
    assert(c.borrow_item("Dichromatic Lotus Butterfly"));
    cout << "\t\tTrying to return Eastern Mystical Love Consultation" << endl;
    assert(!c.return_item("Eastern Mystical Love Consultation"));
    cout << "\t\tReturning Dichromatic Lotus Butterfly" << endl;
    assert(c.return_item("Dichromatic Lotus Butterfly"));
    delete t;
    delete t2;
    cout << "Customer tests pass!" << endl;
}

void test_store() {
    cout << "Testing Store class..." << endl;
    Store s;
    cout << "\tTesting Store.read_inventory()..." << endl;
    assert(s.read_inventory("data/data4movies.txt"));
    cout << "\t\tDisplaying Store inventory..." << endl;
    cout << "\t\t" << endl;
    s.display_inventory();
    cout << "\tTesting Store.read_customers()..." << endl;
    assert(s.read_customers("data/data4customers.txt"));

    cout << "\tTesting Store.read_commands()..." << endl;
    assert(s.read_commands("data/data4commands.txt"));

    cout << "Store tests pass!" << endl;
}

void test_customer_table() {
    cout << "Testing Customer Table class..." << endl;
    CustomerTable ct;
    cout << "\tTesting Customer table simple insertion and retrieval..." << endl;
    Customer c(1001, "Reimu", "Hakurei");
    Customer c2(1002, "Bobby", "Joe");
    ct.insert(c);
    ct.insert(c2);

    std::stringstream s1;
    std::stringstream s2;
    s1 << c;
    s2 << *(ct.retrieve(1001));
    assert(s1.str() == s2.str());
    s1.str("");
    s2.str("");

    cout << "\tTesting Customer table overwriting insertion and retrieval..." << endl;
    Customer c3(1001, "Lelouch", "Lamperouge");
    ct.insert(c3);
    s1 << c3;
    s2 << *(ct.retrieve(1001));
    assert(s1.str() == s2.str());
    s1.str("");
    s2.str("");
    cout << "\tTesting Customer table resizing..." << endl;
    Customer c4(1003, "Suzaku", "Kururugi");
    ct.insert(c4);
    s1 << c4;
    s2 << *ct.retrieve(1003);
    assert(s1.str() == s2.str());
    s1.str("");
    s2.str("");

    cout << "\tTesting Customer table inserting many values..." << endl;

    std::ifstream infile("data/data4customers.txt");
    std::string line;
    int size = 0;

    while (std::getline(infile, line)) {
        std::cout << "\t\t" << line << std::endl;
        std::istringstream stream(line);
        int customer_id;
        std::string first_name, last_name;
        stream >> customer_id >> first_name >> last_name;
        Customer new_customer(customer_id, first_name, last_name);
        ct.insert(Customer(customer_id, first_name, last_name));
        s1 << new_customer;
        s2 << *(ct.retrieve(customer_id));
        assert(s1.str() == s2.str());
        s1.str("");
        s2.str("");
    }

    cout << "\tTesting Customer table retrieving nonexistent key returns null." << endl;
    assert(ct.retrieve(5555) == NULL);

    cout << "\tTesting Customer table simple removal..." << endl;
    ct.remove(1001);
    assert(ct.retrieve(1001) == NULL);

    cout << "CustomerTable tests pass!" << endl;

}

void test_movie() {
    cout << "Testing Movie class..." << std::endl;
    stringstream ss;
    ss.str("0, Aya Shameimaru, Double Spoiler, 2010");
    ComedyMovie* cm = new ComedyMovie(ss);
    ss.clear();
    ss.str("0, Aya Shameimaru, Shoot the Bullet, 2005");
    ComedyMovie* cm2 = new ComedyMovie(ss);
    // item methods
    assert(!cm->remove_stock(1));
    assert(!cm->add_stock(-10));
    assert(cm->add_stock(10));

    // comedy sorting key (title, year)
    cout << "\tComedyMovie sorting keys:" << std::endl;
    cout << "\t\t" << cm->get_key() << std::endl;
    cout << "\t\t" << cm2->get_key() << std::endl;
    assert(cm->get_key().find("Double Spoiler2010") != string::npos);
    assert(*cm < *cm2);

    ss.clear();
    ss.str("15, Hata no Kokoro, Hopeless Masquerade, 2013");
    DramaMovie* dm = new DramaMovie(ss);
    // drama sorting key (director, title)
    cout << "\tDramaMovie sorting keys:" << std::endl;
    cout << "\t\t" << dm->get_key() << std::endl;
    assert(dm->get_key().find("Hata no Kokoro") != string::npos);
    assert(dm->get_key().find("Hopeless Masquerade") != string::npos);

    ss.clear();
    ss.str("4, ZUN Soft, Lotus Land Story, Yuuka Kazami 8 1998");
    ClassicMovie* clm = new ClassicMovie(ss);
    ss.clear();
    ss.str("4, ZUN Soft, Mystic Square, Yuuka Kazami 12 1998");
    ClassicMovie* clm2 = new ClassicMovie(ss);
    // classic sorting key (release date, then major actor)
    cout << "\tClassicMovie sorting keys:" << std::endl;
    cout << "\t\t" << clm->get_key() << std::endl;
    cout << "\t\t" << clm2->get_key() << std::endl;
    assert(clm->get_key().find("199808") != std::string::npos);
    assert(clm->get_key().find("Yuuka Kazami") != std::string::npos);
    assert(*clm < *clm2);
    
    // error case tests?

    delete cm;
    delete cm2;
    delete dm;
    delete clm;
    delete clm2;

    cout << "Movie tests pass!" << endl;
}

void test_itemfactory() {
    cout << "Testing Item, Movie subclasses and ItemFactory..." << endl;
    Item* i = ItemFactory::create_item(
        "C, 4, ZUN Soft, Mystic Square, Alice Margatroid 12 1998");

    cout << "\tItemFactory: Movie creation (string arg)" << endl;
    assert(i != NULL);
    cout << "\t\t" << i->get_key() << endl;
    assert(i->get_typecode() == 'C');
    assert(i->get_key().find("199812") != string::npos);

    cout << "\tItemFactory: Movie creation (stream arg)" << std::endl;
    stringstream ss("D, 6, TSA, Embodiment of Scarlet Devil, 2002\nD, 7, TSA, Perfect Cherry Blossom, 2003\n");
    Item* i2 = ItemFactory::create_item(ss);
    assert(i2 != NULL);
    // correct movie construction?
    cout << "\t\t" << i2->get_key() << std::endl;
    assert(i2->get_key().find("Embodiment of Scarlet Devil") != string::npos);
    assert(i2->get_key().find("Perfect Cherry Blossom") == string::npos);

    cout << "\tItemFactory doesn't destroy second entry:" << endl;
    // stream is in a good state?
    cout << "\t\tD, 6, TSA, Embodiment of Scarlet Devil, 2002\n\t\tD, 7, TSA, Perfect Cherry Blossom, 2003\n" << endl;
    // i don't know if it's okay that the other string is still there...
    assert(ss.str().find("D, 7, TSA, Perfect Cherry Blossom, 2003\n") != string::npos);

    cout << "\tItemFactory fails on bad item typecode:" << endl;
    std::cerr << "\t\t";
    Item* i3 = ItemFactory::create_item("X, 0, junk data, junk data, 2020");
    assert(i3 == NULL);

    cout << "\tItemFactory rejects bad data on key request:" << endl;
    std::cerr << "\t\t";
    assert(ItemFactory::item_data_to_key("Y 2 1971 Ruth Gordon") == "");

    cout << "\tItemFactory correctly transforms classic data to key:" << endl;
    cout << "\t\t" << ItemFactory::item_data_to_key("C 12 1998 Alice Margatroid") << endl;
    assert(ItemFactory::item_data_to_key("C 12 1998 Alice Margatroid")
           == i->get_key());

    cout << "\tItemFactory correctly transforms drama data to key:" << endl;
    cout << "\t\t" << ItemFactory::item_data_to_key("D TSA, Embodiment of Scarlet Devil,") << endl;
    assert(ItemFactory::item_data_to_key("D TSA, Embodiment of Scarlet Devil,")
           == i2->get_key());
    
    delete i;
    delete i2;
    delete i3;

    cout << "ItemFactory tests pass!" << std::endl;
}

void test_transaction() {
    cout << "Testing TransactionFactory, Transaction class and subclasses ... " << endl;
    stringstream s1;
    stringstream s2;
    cout << "\tTest that TransactionFactory creates Transactions of the appropriate subclass" << endl;
    Transaction* borrow_t = TransactionFactory::create_transaction("B 1234 D D Steven Spielberg, Schindler's List,");
    assert(borrow_t->get_transaction_type() == 'B');
    cout << "\t\t" << borrow_t << endl;
    s1 << borrow_t;
    s2 << "B 1234 D D Steven Spielberg, Schindler's List,";
    assert(s1.str() == s2.str());
    s1.str("");
    s2.str("");

    Transaction* return_t = TransactionFactory::create_transaction("R 1234 D C 9 1938 Katherine Hepburn");
    assert(return_t->get_transaction_type() == 'R');
    cout << "\t\t" << return_t << endl;
    s1 << return_t;
    s2 << "R 1234 D C 9 1938 Katherine Hepburn";
    assert(s1.str() == s2.str());
    s1.str("");
    s2.str("");

    Transaction* inventory_t = TransactionFactory::create_transaction("I");
    assert(inventory_t->get_transaction_type() == 'I');
    cout << "\t\t" << inventory_t << endl;
    s1 << inventory_t;
    s2 << "I";
    assert(s1.str() == s2.str());
    s1.str("");
    s2.str("");

    Transaction* history_t = TransactionFactory::create_transaction("H 1234");
    assert(history_t->get_transaction_type() == 'H');
    s1 << history_t;
    s2 << "H 1234 ";
    cout << "\t\t" << history_t << endl;

    assert(s1.str() == s2.str());
    s1.str("");
    s2.str("");

    cout << "\tTest that TransactionFactory returns NULL when given invalid type" << endl;
    std::cerr << "\t\t";
    Transaction* invalid_t = TransactionFactory::create_transaction("X 1234 Z C 9 1938 Katherine Hepburn");
    assert(invalid_t == NULL);
}

int main() {
    test_customer();
    test_store();
    test_customer_table();
    test_movie();
    test_itemfactory();
    test_transaction();
}
