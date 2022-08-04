#include "utils.hpp"

template <typename iter>
void quick_sort(iter first, iter last) {
  if (last - first <= 1) return;

  auto f = [last](const auto& x) { return x < *(last - 1); };
  auto mid = std::partition(first, last - 1, f);
  std::iter_swap(mid, last - 1);

  quick_sort(first, mid);
  quick_sort(mid + 1, last);
}

template <typename iter>
void merge_sort(iter first, iter last) {
  if (last - first <= 1) return;

  auto mid = first + (last - first) / 2;
  merge_sort(first, mid);
  merge_sort(mid, last);
  inplace_merge(first, mid, last);
}

vector<int> v(10);
int main() {
  // generate(v.begin(), v.end(), []() { return rand() % 100; });
  iota(v.begin(), v.end(), 1);
  random_shuffle(v.begin(), v.end());
  print(v);
  quick_sort(v.begin(), v.end());
  print(v, "[Quick Sort]:");

  random_shuffle(v.begin(), v.end());
  print(v);
  merge_sort(v.begin(), v.end());
  print(v, "[Merge Sort]:");

  return 0;
}