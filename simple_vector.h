#pragma once

#include <cstdlib>

template <typename T>
class SimpleVector {
public:
  SimpleVector() {
      data = nullptr;
      size = 0;
      capacity = 0;
  }

  explicit SimpleVector(size_t size_) {
      data = new T[size_];
      capacity = size_;
      size = size_;
  }

  ~SimpleVector() {
      delete[] data;
  }

  T& operator[](size_t index) {
      return data[index];
  }

  T* begin() {
      return data;
  }

  T* end() {
      return data + size;
  }

  size_t Size() const {
      return size;
  }

  size_t Capacity() const {
      return capacity;
  }

  void PushBack(const T& value) {
      if (size == 0) {
          capacity = 1;
          ++size;
          delete[] data;
          data = new T[1];
          data[0] = value;
      } else if (size != capacity) {
          data[size] = value;
          ++size;
      } else {
          capacity *= 2;
          T *tmp = new T[size];
          for (size_t i = 0; i < size; ++i) {
              tmp[i] = data[i];
          }
          delete[] data;
          data = new T[capacity];
          for (size_t i = 0; i < size; ++i) {
              data[i] = tmp[i];
          }
          data[size] = value;
          ++size;
          delete[] tmp;
      }
  }

private:
    T* data;
    size_t size;
    size_t capacity;
};
