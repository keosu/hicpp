#include <boost/pfr.hpp>
#include <iostream>
#include <string>

struct comparable_struct {  // No operators defined for that structure
  int i;
  short s;
  //   char data[7];
  std::string str;
  bool bl;
  int a, b, c, d, e, f;
  //   char str[7];
};
// ...
struct sample {
  char a;
  float f;
};
int main() {
  sample var{'f', 2.345};
  boost::pfr::get<1>(var) = 1.2;

  std::cout << boost::pfr::get<0>(var) << " " << var.f << std::endl;  // 1.2
  comparable_struct s1{0, 1, "hello world", false, 6, 7, 8, 9, 10, 11};
  std::cout << boost::pfr::io(s1);  // Outputs: {0, 1, H, e, l, l, o, , , 0, 6, 7, 8, 9, 10, 11}
}