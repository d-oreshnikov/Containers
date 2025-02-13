#ifndef CONTAINERS_SRC_QUEUE_MY_QUEUE_H_
#define CONTAINERS_SRC_QUEUE_MY_QUEUE_H_

#include <iostream>
#include <stdexcept>

namespace my {
template <typename T>
class queue {
 public:
  //  type aliases
  using value_type = T;           // value type in queue
  using size_type = std::size_t;  // value type for queue size
  using reference = T&;
  using const_reference = const T&;  // const pointer for element in queue

  //  constructors and destructor
  queue();
  queue(std::initializer_list<value_type> const&
            items);  //  constructor for my::queue<int> q = {1, 2, 3, 4, 5}
  queue(const queue& q);  //  constructor for deep copy another queue
  queue(queue&& q);       // constructor for move
  ~queue();               //  destructor

  // assignment operator
  queue& operator=(queue&& q) {
    if (this != &q) {
      swap(q);
    }
    return *this;
  }

  // element access
  const_reference front();
  const_reference back();

  // capacity
  bool empty();
  size_type size();

  // modifiers
  void push(const_reference value);
  void pop();
  void swap(queue& other);

  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  struct node {
    value_type data;
    node* next;
  };

  node* head;
  node* tail;
  size_type sz;

};  //  class queue

template <typename T>
template <typename... Args>
void queue<T>::insert_many_back(Args&&... args) {
  (push(std::forward<Args>(args)), ...);
}

//  constructors and destructor
template <typename T>
queue<T>::queue() : head(nullptr), tail(nullptr), sz(0) {}

template <typename T>
queue<T>::queue(std::initializer_list<value_type> const& items) : queue() {
  for (auto const& item : items) {
    push(item);
  }
}

template <typename T>
queue<T>::queue(const queue& q) : queue() {
  for (node* current = q.head; current != nullptr; current = current->next) {
    push(current->data);
  }
}

template <typename T>
queue<T>::queue(queue&& q) : queue() {
  swap(q);
}

template <typename T>
queue<T>::~queue() {
  while (head != nullptr) {
    pop();
  }
}

// element access
template <typename T>
typename queue<T>::const_reference queue<T>::front() {
  if (empty()) {
    throw std::out_of_range("queue::front(): queue is empty");
  }
  return head->data;
}

template <typename T>
typename queue<T>::const_reference queue<T>::back() {
  if (empty()) {
    throw std::out_of_range("queue::front(): queue is empty");
  }
  return tail->data;
}

// capacity

template <typename T>
bool queue<T>::empty() {
  return sz == 0;
}

template <typename T>
typename queue<T>::size_type queue<T>::size() {
  return sz;
}

// modifiers

template <typename T>
void queue<T>::push(const_reference value) {
  node* new_node = new node{value, nullptr};
  if (empty()) {
    head = new_node;
  } else {
    tail->next = new_node;
  }
  tail = new_node;
  ++sz;
}

template <typename T>
void queue<T>::pop() {
  if (empty()) {
    throw std::out_of_range("queue::pop(): queue is empty");
  }
  node* old_head = head;
  head = head->next;
  delete old_head;
  --sz;
}

template <typename T>
void queue<T>::swap(queue& other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(sz, other.sz);
}

}  // namespace my

#endif  // CONTAINERS_SRC_QUEUE_MY_QUEUE_H_