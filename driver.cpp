#include <assert.h>
#include <iostream>
#include <sstream>
#include "customer.h"
#include "store.h"

using namespace std;

bool test_customer() {
  cout << "Testing Customer class..." << endl;
  bool success = true;
  Customer c(1001, "Reimu", "Hakurei");
  ostringstream s;
  s << c;
  cout << c;
  success &= s.str() == "Customer 1001, Reimu Hakurei history:\n";
  // requires Transaction class
  // c.record_transaction(Transaction());
  return success;
}

bool test_store() {
  cout << "Testing Store class..." << endl;
  
  Store s;
  cout << "Testing Store.read_customers()..." << endl;
  assert(s.read_customers("data/data4customers.txt"));
  return true;
}

int main() {
  bool t;
  cout << boolalpha;
  t = test_customer();
  cout << "Customer tests pass: " << t << endl;

  bool t2;
  t = test_store();
  cout << "Store tests pass: " << t << endl;

}
