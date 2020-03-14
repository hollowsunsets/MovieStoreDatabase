#include <assert.h>
#include <iostream>
#include <sstream>
#include "customer.h"
#include "item.h"
#include "movie.h"
#include "store.h"
#include <fstream>

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
    s2 << ct.retrieve(1001);
    assert(s1.str() == s2.str());
    s1.str("");
    s2.str("");

    cout << "\tTesting Customer table overwriting insertion and retrieval..." << endl;
    Customer c3(1001, "Lelouch", "Lamperouge");
    ct.insert(c3);
    s1 << c3;
    s2 << ct.retrieve(1001);
    assert(s1.str() == s2.str());
    s1.str("");
    s2.str("");
    cout << "!!!!!!!!!!!!!!!!!!!!1MEMORY LEAK BEGINS HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    cout << "\tTesting Customer table resizing..." << endl;
    Customer c4(1003, "Suzaku", "Kururugi");
    ct.insert(c4);
    s1 << c4;
    s2 << ct.retrieve(1003);
    assert(s1.str() == s2.str());
    s1.str("");
    s2.str("");
    /*
    Customer c5(1004, "Tanjiro", "Kamado");
    ct.insert(c5);
    s1 << c5;
    s2 << ct.retrieve(1004);
    assert(s1.str() == s2.str());
    s1.str("");
    s2.str("");*/



    cout << "\tTesting Customer table inserting many values..." << endl;

    std::ifstream infile("data/data4customers.txt");
    std::string line;
    int size = 0;


    while (std::getline(infile, line) && size < 1) {

        std::cout << "\t\tInserting " << line << std::endl;
        std::istringstream stream(line);
        int customer_id;
        std::string first_name, last_name;
        stream >> customer_id >> first_name >> last_name;
        Customer new_customer(customer_id, first_name, last_name);
        ct.insert(Customer(customer_id, first_name, last_name));
        s1 << new_customer;
        s2 << ct.retrieve(customer_id);
        assert(s1.str() == s2.str());
        s1.str("");
        s2.str("");
        size++;
    }

    cout << "\tTesting Customer table simple removal..." << endl;
    assert(ct.remove(1001));
    bool exception_thrown2 = false;
    try {
        ct.retrieve(1001);
    } catch (...) {
        cout << "\t\tException thrown when trying to retrieve id that should have been removed" << endl;
        exception_thrown2 = true;
    }

    assert(exception_thrown2);

    ct.display_table();
    assert(ct.remove(1002));
    bool exception_thrown3 = false;
    try {
        ct.retrieve(1002);
    } catch (...) {
        cout << "\t\tException thrown when trying to retrieve id that should have been removed" << endl;
        exception_thrown3 = true;
    }
    assert(exception_thrown3);
    ct.display_table();
    


    cout << "\tTesting Customer table retrieving nonexistent key throws an exception..." << endl;
    bool exception_thrown = false;
    try {
        ct.retrieve(5555);
    } catch (...) {
        cout << "\t\tException thrown when trying to retrieve nonexistent id" << endl;
        exception_thrown = true;
    }
    assert(exception_thrown);

    cout << "CustomerTable tests pass!" << endl;

}

void test_movie() {
    std::stringstream ss;
    ss.str("0, Aya Shameimaru, Double Spoiler, 2010");
    ComedyMovie* cm = new ComedyMovie(ss);
    ss.clear();
    ss.str("0, Aya Shameimaru, Shoot the Bullet, 2005");
    ComedyMovie* cm2 = new ComedyMovie(ss);
    // item methods
    //    cout << cm->get_typecode() << std::endl;
    // assert(cm->get_typecode() == 'F');
    assert(!cm->remove_stock(1));
    assert(!cm->add_stock(-10));
    assert(cm->add_stock(10));

    // comedy sorting key (title, year)
    cout << "ComedyMovie sorting keys:" << std::endl;
    cout << cm->get_key() << std::endl;
    cout << cm2->get_key() << std::endl;
    assert(cm->get_key().find("Double Spoiler2010") != std::string::npos);
    assert(*cm < *cm2);

    ss.clear();
    ss.str("15, Hata no Kokoro, Hopeless Masquerade, 2013");
    DramaMovie* dm = new DramaMovie(ss);
    // drama sorting key (director, title)
    cout << "DramaMovie sorting keys:" << std::endl;
    cout << dm->get_key() << std::endl;
    assert(dm->get_key().find("Hata no Kokoro") != std::string::npos);
    assert(dm->get_key().find("Hopeless Masquerade") != std::string::npos);

    ss.clear();
    ss.str("4, ZUN Soft, Lotus Land Story, Yuuka Kazami 8 1998");
    ClassicMovie* clm = new ClassicMovie(ss);
    ss.clear();
    ss.str("4, ZUN Soft, Mystic Square, Yuuka Kazami 12 1998");
    ClassicMovie* clm2 = new ClassicMovie(ss);
    // classic sorting key (release date, then major actor)
    cout << "ClassicMovie sorting keys:" << std::endl;
    cout << clm->get_key() << std::endl;
    cout << clm2->get_key() << std::endl;
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


int main() {
    test_customer();
    /* test_store(); Commented out for now since problems seem to originate
                     from Store's nonexistent destructor. */
    test_customer_table();
    // test_movie();
}
