#include <string>

// glorified struct
class transaction {
 public:
  char transaction_type;
  unsigned short customer_id;
  char item_type;
  char item_typecode;
  std::string item_data;
};
