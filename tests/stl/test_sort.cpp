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

template <typename iter, typename F>
void heap_sort(iter first, iter last, F f = std::less<>{}) {
  std::make_heap(first, last, f);

  while (first != last) std::pop_heap(first, last--, f);
}

template <class It, class Comp>
void partition(It first, It last, Comp f) {
  while (first < last) {
    while (first < last && f(first)) first++;
    while (first < last && !f(last)) last--;
    if (first < last) }
}

template <class ForwardIt, class UnaryPredicate>
ForwardIt partitionx(ForwardIt first, ForwardIt last, UnaryPredicate p) {
  first = std::find_if_not(first, last, p);
  if (first == last) return first;

  for (ForwardIt i = std::next(first); i != last; ++i) {
    if (p(*i)) {
      std::iter_swap(i, first);
      ++first;
    }
  }
  return first;
}

template <class InIt1, class InIt2, class OutIt>
OutIt merge(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2, OutIt d_first) {
  while (first1 != last1) {
    if (first2 == last2) {
      return std::copy(first1, last1, d_first);
    }
    if (*first2 < *first1) {
      *d_first = *first2;
      ++first2;
    } else {
      *d_first = *first1;
      ++first1;
    }
    ++d_first;
  }
  return std::copy(first2, last2, d_first);
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

  random_shuffle(v.begin(), v.end());
  print(v);
  heap_sort(v.begin(), v.end(), std::greater<>{});
  print(v, "[Heap Sort]:");

  random_shuffle(v.begin(), v.end());
  print(v);
  heap_sort(v.begin(), v.end(), std::less<>{});
  print(v, "[Heap Sort]:");

  return 0;
}