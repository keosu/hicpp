#include <algorithm>
#include <boost/algorithm/string/trim_all.hpp> 
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <iterator>
#include <vector>

using namespace boost::algorithm;

int main() {

  std::string s = "   hello  world!!! ";
  std::cout << trim_copy(s) << std::endl; 
  std::cout << trim_all_copy(s) << std::endl; 

  std::vector<std::string> vec;
  split(vec, "a b  c\td\ne   g ", boost::is_any_of(" \t\n"), token_compress_on);


  std::string str6 = join(vec,"##");
  std::cout<<str6<<std::endl;

  return 0;
}