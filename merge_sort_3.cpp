#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  if (range_end - range_begin < 2) {
    return;
  }
  std::vector<typename RandomIt::value_type> tmp(std::make_move_iterator(range_begin), std::make_move_iterator(range_end));
  size_t length = (tmp.end() - tmp.begin()) / 3;
  MergeSort(tmp.begin(), tmp.begin() + length);
  MergeSort(tmp.begin() + length, tmp.begin() + 2 * length);
  MergeSort(tmp.begin() + 2 * length, tmp.end());
  std::vector<typename RandomIt::value_type> tmp_;
  std::merge(std::make_move_iterator(tmp.begin()), std::make_move_iterator(tmp.begin() + length),
             std::make_move_iterator(tmp.begin() + length), std::make_move_iterator(tmp.begin() + 2 * length),
             std::back_inserter(tmp_));
  std::merge(std::make_move_iterator(tmp_.begin()), std::make_move_iterator(tmp_.end()),
             std::make_move_iterator(tmp.begin() + 2 * length), std::make_move_iterator(tmp.end()),
             range_begin);
}
