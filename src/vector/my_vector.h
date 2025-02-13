#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>

namespace my {
template <typename T>
class vector {
 private:
  T* begin_;
  T* end_;
  T* AllEnd_;

 public:
  /* Member type */
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  /* Functions */
  vector() noexcept;
  vector(size_type n);
  vector(std::initializer_list<value_type> const& items);
  vector(const vector& v);
  vector(vector&& v) noexcept;
  ~vector() noexcept;
  vector<T>& operator=(vector&& v);

  /* Element access */
  reference at(size_type pos);
  reference operator[](size_type pos) const noexcept;
  const_reference front() const noexcept;
  const_reference back() const noexcept;
  T* data() const noexcept;

  /* Iterators */
  iterator begin() const noexcept;
  iterator end() const noexcept;

  /* Capacity */
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void reserve(size_type size);
  size_type capacity() const noexcept;
  void shrink_to_fit();

  /* Modifiers */
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);

  /* Modifiers extra */
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  // Help Functions
  void initializeFromItems(iterator start, const_iterator end,
                           const_iterator listIt);
  void reallocation(size_t size);
  void full_clear();
  void swap(vector&& v);
};
}  // namespace my

template <typename T>
void my::vector<T>::initializeFromItems(iterator start, const_iterator end,
                                         const_iterator listIt) {
  auto it = start;
  try {
    for (; it != end; ++it, ++listIt) {
      new (it) T(*listIt);
    }
  } catch (...) {
    for (iterator delit = start; delit != it; ++delit) {
      delit->~T();
    }
    delete[] reinterpret_cast<uint8_t*>(start);
    throw;
  }
  return;
}
template <typename T>
void my::vector<T>::full_clear() {
  for (iterator del = begin_; del != end_; ++del) {
    del->~T();
  }

  delete[] reinterpret_cast<uint8_t*>(begin_);
  begin_ = nullptr;
  end_ = nullptr;
  AllEnd_ = nullptr;
  return;
}

template <typename T>
void my::vector<T>::swap(vector&& v) {
  std::swap(begin_, v.begin_);
  std::swap(end_, v.end_);
  std::swap(AllEnd_, v.AllEnd_);
  return;
}

template <typename T>
void my::vector<T>::reallocation(size_t size) {
  T* newarr_ = reinterpret_cast<T*>(new uint8_t[size * sizeof(T)]);
  size_type objQuant = this->size();

  initializeFromItems(newarr_, newarr_ + objQuant, begin_);
  this->full_clear();

  begin_ = newarr_;
  end_ = newarr_ + objQuant;
  AllEnd_ = newarr_ + size;
}

/* Итератор начала */
template <typename T>
typename my::vector<T>::iterator my::vector<T>::begin() const noexcept {
  return begin_;
}

/* Итератор конца */
template <typename T>
typename my::vector<T>::iterator my::vector<T>::end() const noexcept {
  return end_;
}

/* Очищает содержимое */
template <typename T>
void my::vector<T>::clear() noexcept {
  for (iterator del = begin_; del != end_; ++del) {
    del->~T();
  }
  end_ = begin_;
  return;
}

/* Вставляет элементы на конкретную позицию и возвращает итератор, указывающий
   на новый элемент */
template <typename T>
typename my::vector<T>::iterator my::vector<T>::insert(
    iterator pos, const_reference value) {
  if (pos < begin_ || pos > end_)
    throw std::out_of_range("Iterator is out of range");

  if (pos == end_) {
    this->push_back(value);
    pos = end();
    return --pos;
  }

  size_type index = pos - begin_;

  if (end_ == AllEnd_) {
    reserve(std::max<size_t>(1, 2 * capacity()));
  }
  pos = begin_ + index;

  new (end_) T(*(end_ - 1));

  for (iterator it = end_ - 1; it != pos; --it) {
    *it = std::move(*(it - 1));
  }

  try {
    pos->~T();
    new (pos) T(value);
  } catch (...) {
    for (iterator it = pos; it != end_; ++it) {
      *it = std::move(*(it + 1));
    }
    end_->~T();
    throw;
  }
  ++end_;
  return pos;
}
/* Cтирает элемент в позиции */
template <typename T>
void my::vector<T>::erase(iterator pos) {
  if (pos < begin_ || pos >= end_)
    throw std::out_of_range("Iterator is out of range");

  auto it = pos;
  try {
    for (; it != end_ - 1; ++it) {
      (it)->~T();
      new (it) T(*(it + 1));
    }
    --end_;
  } catch (...) {
    for (iterator delit = pos; delit != it; ++delit) {
      delit->~T();
    }
    throw;
  }
}

/* Добавляет элемент в конец */
template <typename T>
void my::vector<T>::push_back(const_reference value) {
  if (end_ == AllEnd_) {
    reserve(std::max<size_t>(1, 2 * capacity()));
  }

  try {
    new (end_) T(value);
  } catch (...) {
    end_->~T();
    throw;
  }
  ++end_;
}

/* Удаляет последний элемент */
template <typename T>
void my::vector<T>::pop_back() {
  if (end_ != begin_) {
    --end_;
    end_->~T();
  }
}

/* Меняет содержимое */
template <typename T>
void my::vector<T>::swap(vector& other) {
  std::swap(begin_, other.begin_);
  std::swap(end_, other.end_);
  std::swap(AllEnd_, other.AllEnd_);
}

/* Вставка новых элементов в контейнер непосредственно перед pos */
template <typename T>
template <typename... Args>
typename my::vector<T>::iterator my::vector<T>::insert_many(
    const_iterator pos, Args&&... args) {
  if (pos < begin_ || pos > end_)
    throw std::out_of_range("Iterator is out of range");

  size_type index = pos - begin_;

  size_t args_count = sizeof...(Args);

  if (begin_ == nullptr || end_ + args_count >= AllEnd_) {
    reserve(std::max<size_t>(args_count, 2 * (size() + args_count)));
    pos = begin_ + index;
  }

  iterator insert_pos = begin_ + index;

  iterator it = end_ + args_count - 1;
  auto count = end_ - pos;
  try {
    for (iterator k = end_; count != 0; --it, --count) {
      new (it) T(*(--k));
    }
  } catch (...) {
    for (iterator delit = end_ + args_count - 1; delit != it; --delit) {
      delit->~T();
    }
  }

  for (iterator it = insert_pos; it != insert_pos + args_count; ++it) {
    it->~T();
  }

  size_t index_in_args = 0;
  try {
    ((new (insert_pos + index_in_args++) T(args)), ...);
  } catch (...) {
    iterator k = insert_pos + index_in_args;
    for (iterator delit = insert_pos; delit != k; ++delit) {
      delit->~T();
    }
  }

  end_ += args_count;
  return insert_pos;
}

/* Добавляет новые элементы в конец контейнера */
template <typename T>
template <typename... Args>
void my::vector<T>::insert_many_back(Args&&... args) {
  insert_many(end(), std::forward<Args>(args)...);
}

/* Проверяет пустой ли контейнер */
template <typename T>
bool my::vector<T>::empty() const noexcept {
  return capacity() == 0;
}

/* Возвращает количество элементов */
template <typename T>
typename my::vector<T>::size_type my::vector<T>::size() const noexcept {
  return end_ - begin_;
}

/* Возвращает максимально возможное количество элементов */
template <typename T>
typename my::vector<T>::size_type my::vector<T>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

/* Выделяет хранилище элементов и копирует текущие элементы во вновь выделенный
 * массив */
template <typename T>
void my::vector<T>::reserve(size_t size) {
  if (capacity() >= size) return;
  reallocation(size);
}

/* Возвращает количество элементов, которые могут хранится в выделенном на
 * данный момент хранилище */
template <typename T>
typename my::vector<T>::size_type my::vector<T>::capacity() const noexcept {
  return AllEnd_ - begin_;
}

/* Освобождение неиспользуемой памяти */
template <typename T>
void my::vector<T>::shrink_to_fit() {
  if (capacity() == size()) return;
  reallocation(size());
}

/* Доступ к элементу с проверкой границ */
template <typename T>
typename my::vector<T>::reference my::vector<T>::at(size_type pos) {
  if (pos >= size())
    throw std::out_of_range("incorrect size index");
  else
    return *(begin_ + pos);
}

/* Доступ к указанному элементу */
template <typename T>
typename my::vector<T>::reference my::vector<T>::operator[](
    size_type pos) const noexcept {
  return *(begin_ + pos);
}

/* Доступ к первому элементу */
template <typename T>
typename my::vector<T>::const_reference my::vector<T>::front()
    const noexcept {
  return *(begin_);
}

/* Доступ к последнему элементу */
template <typename T>
typename my::vector<T>::const_reference my::vector<T>::back() const noexcept {
  return *(end_ - 1);
}

/* Прямой доступ к базовому массиву */
template <typename T>
T* my::vector<T>::data() const noexcept {
  return begin_;
}

/* По умолчанию */
template <typename T>
my::vector<T>::vector() noexcept
    : begin_(nullptr), end_(nullptr), AllEnd_(nullptr) {}

/* Параметризованный */
template <typename T>
my::vector<T>::vector(size_type n)
    : begin_(
          reinterpret_cast<value_type*>(new uint8_t[n * sizeof(value_type)])),
      end_(begin_ + n),
      AllEnd_(begin_ + n) {
  iterator it = begin_;
  try {
    for (; it != end_; ++it) {
      new (it) T();
    }
  } catch (...) {
    for (iterator delit = begin_; delit != it; ++delit) {
      delit->~T();
    }
    delete[] reinterpret_cast<uint8_t*>(begin_);
    throw;
  }
}

/* Списка инициализаторов */
template <typename T>
my::vector<T>::vector(std::initializer_list<value_type> const& items)
    : begin_(reinterpret_cast<value_type*>(
          new uint8_t[items.size() * sizeof(value_type)])),
      end_(begin_ + items.size()),
      AllEnd_(begin_ + items.size()) {
  initializeFromItems(begin_, end_, items.begin());
}

/* Копирования */
template <typename T>
my::vector<T>::vector(const vector& v)
    : begin_(reinterpret_cast<value_type*>(
          new uint8_t[v.size() * sizeof(value_type)])),
      end_(begin_ + v.size()),
      AllEnd_(begin_ + v.size()) {
  initializeFromItems(begin_, end_, v.begin_);
}

/* Перемещения */
template <typename T>
my::vector<T>::vector(vector&& v) noexcept
    : begin_(v.begin_), end_(v.end_), AllEnd_(v.AllEnd_) {
  v.begin_ = nullptr;
  v.end_ = nullptr;
  AllEnd_ = nullptr;
}
/* Деструктор */
template <typename T>
my::vector<T>::vector::~vector() noexcept {
  full_clear();
}

/* Присваивание перемещением */
template <typename T>
my::vector<T>& my::vector<T>::operator=(vector&& v) {
  if (this == &v) return *this;
  full_clear();
  begin_ = v.begin_;
  end_ = v.end_;
  AllEnd_ = v.AllEnd_;
  v.begin_ = nullptr;
  v.end_ = nullptr;
  v.AllEnd_ = nullptr;
  return *this;
}

#endif
