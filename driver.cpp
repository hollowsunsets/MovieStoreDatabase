#include <assert.h>
#include <iostream>
#include <sstream>
#include "customer.h"
#include "item.h"
#include "movie.h"
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
    cout << "comparison? " << (cm < cm2) << std::endl;
    assert(cm < cm2);

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
    assert(clm < clm2);
    
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
    test_store();
    test_movie();
}
