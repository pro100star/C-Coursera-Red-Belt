#include <cstdint>
#include <iterator>
#include <list>
#include <numeric>
#include <vector>

using namespace std;

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
  list<typename RandomIt::value_type> pool;
  auto it = first;
  for (size_t i = 0; i < last - first; ++i) {
    pool.push_back(move(*(it++)));
  }
  auto it_ = pool.begin();
  while (!pool.empty()) {
    *(first++) = move(*it_);
    it_ = pool.erase(it_);
    if (it_ == pool.end()) {
      it_ = pool.begin();
    }
    for (size_t i = 0; i < step_size - 1; ++i) {
      if (++it_ == pool.end()) {
        it_ = pool.begin();
      }
    }
    if (pool.empty()) {
      break;
    }
  }
}
