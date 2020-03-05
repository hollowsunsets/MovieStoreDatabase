#include <cassert>
#include <iostream>
#include <sstream>
#include "customer.h"
#include "store.h"

using namespace std;

bool test_customer() {
  bool success = true;
  Customer c(1001, "Reimu", "Hakurei");
  ostringstream s;
  s << c;
  cout << c;
  success &= s.str() == "Customer 1001, Reimu Hakurei history:\n";

  // requires Transaction class
  //c.record_transaction(Transaction());
  return success;
}

bool test_store() {
  Store s;

}

int main() {
  /*
  bool t;
  cout << boolalpha;
  t = test_customer();
  cout << "Customer tests pass: " << t << std::endl;*/
}
