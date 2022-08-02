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

//////////////////////////////////////////////////////
bool IsOdd(int i) { return (i % 2) == 1; }
void test_partition() {
  vector<int> v(10);
  iota(v.begin(), v.end(), 1);

  auto bound = partition(v.begin(), v.end(), IsOdd);
  print(v.begin(), bound, "[odd val]:");
  print(bound, v.end(), "[even val]:");
}

//////////////////////////////////////////////////////
// function generator :
int RandomNumber() { return (rand() % 100); }
// class generator:
struct c_unique {
  int current;
  c_unique() { current = 0; }
  int operator()() { return ++current; }
} UniqueNumber;

int test_generate() {
  srand(unsigned(time(0)));

  vector<int> v(8);

  generate(v.begin(), v.end(), RandomNumber);
  print(v, "[Random]:");

  generate(v.begin(), v.end(), UniqueNumber);
  print(v, "[GenFunc]:");

  return 0;
}

//////////////////////////////////////////////////////
int op_increase(int i) { return ++i; }

void test_transform() {
  vector<int> foo(10);
  vector<int> bar(10);

  iota(foo.begin(), foo.end(), 1);

  // unary op
  transform(foo.begin(), foo.end(), bar.begin(), op_increase);
  // binary op: plus adds together its two arguments:
  transform(foo.begin(), foo.end(), bar.begin(), foo.begin(), plus<int>());

  print(foo, "[transform]:");
}

//////////////////////////////////////////////////////
void test_merge() {
  int first[] = {5, 10, 15, 20, 25};
  int second[] = {50, 40, 30, 20, 10};
  std::vector<int> v(10);

  std::sort(first, first + 5);
  std::sort(second, second + 5);
  std::merge(first, first + 5, second, second + 5, v.begin());

  print(first, first + 5, "[In a]:");
  print(second, second + 5, "[In b]:");
  print(v, "[Merged]:");
}

int main() {
  vector<int> v(10);

  fill(v.begin(), v.end(), 6);
  print(v);

  fill(v.begin(), v.end() - 2, 5);
  print(v);

  iota(v.begin(), v.end(), 1);
  print(v);

  reverse(v.begin(), v.end());
  print(v);

  rotate(v.begin(), v.begin() + 4, v.end());
  print(v);

  iota(v.begin(), v.end(), 1);
  rotate(v.begin(), v.begin() + 4, v.end() - 1);
  print(v);

  test_partition();
  test_generate();
  test_transform();
  test_merge();

  return 0;
}
