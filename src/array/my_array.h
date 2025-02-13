#ifndef CONTAINERS_SRC_ARRAY_MY_ARRAY_H_
#define CONTAINERS_SRC_ARRAY_MY_ARRAY_H_

#include <iostream>

namespace my {
template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;
  using iterator = T*;
  using const_iterator = const T*;

  // constructors and destructor
  array();
  array(std::initializer_list<value_type> const& items);
  array(const array& a);
  array(array&& a);
  ~array();

  // assignment operator
  array& operator=(array&& a) {
    if (this != &a) {
      swap(a);
    }
    return *this;
  }

  // element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  // changed data to getData to avoid conflict with std::array::data[N]
  iterator getData();

  // array iterators
  iterator begin();
  iterator end();

  // array capacity
  bool empty();
  size_type size();
  size_type max_size();

  // array modifiers
  void swap(array& other);
  void fill(const_reference value);

 private:
  value_type data[N];
};

// constructors and destructor
template <typename T, std::size_t N>
array<T, N>::array() {}

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const& items) {
  std::size_t i = 0;
  for (auto const& item : items) {
    data[i++] = item;
  }
}

template <typename T, std::size_t N>
array<T, N>::array(const array& a) {
  for (std::size_t i = 0; i < N; ++i) {
    data[i] = a.data[i];
  }
}

template <typename T, std::size_t N>
array<T, N>::array(array&& a) {
  swap(a);
}

template <typename T, std::size_t N>
array<T, N>::~array() {}

// element access
template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("array::at");
  }
  return data[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return data[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() {
  return data[0];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() {
  return data[N - 1];
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::getData() {
  return data;
}

// array iterators
template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return data;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return data + N;
}

// array capacity
template <typename T, std::size_t N>
bool array<T, N>::empty() {
  return N == 0;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() {
  return N;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() {
  return N;
}

// array modifiers
template <typename T, std::size_t N>
void array<T, N>::swap(array& other) {
  std::swap_ranges(begin(), end(), other.begin());
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  for (std::size_t i = 0; i < N; ++i) {
    data[i] = value;
  }
}

}  // namespace my

#endif  // CONTAINERS_SRC_ARRAY_MY_ARRAY_H_