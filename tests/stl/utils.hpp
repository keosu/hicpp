
#include <algorithm>  // partition
#include <cstdlib>    // rand, srand
#include <ctime>      // time
#include <iostream>   // cout
#include <iostream>
#include <iterator>  // ostream_iterator
#include <numeric>   // iota
#include <vector>    // vector

using namespace std;

template <typename T>
void print(T first, T last, string header = "", const char* sep = " ") {
  if (header != "") cout << header << "\n\t";
  copy(first, last, ostream_iterator<int>(cout, sep));
  cout << endl;
}

template <typename T>
void print(T v, string header = "", const char* sep = " ") {
  if (header != "") cout << header << "\n\t";
  copy(v.begin(), v.end(), ostream_iterator<int>(cout, sep));
  cout << endl;
}
