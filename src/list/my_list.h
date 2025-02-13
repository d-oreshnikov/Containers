#ifndef CONTAINERS_LIST_MY_LIST_H_
#define CONTAINERS_LIST_MY_LIST_H_

namespace my {
template <class T>
class list {
 private:
  struct Node {
    Node *prev_;
    Node *next_;
    T value_;

    Node(T value = T{}) : prev_(nullptr), next_(nullptr), value_(value) {}
  };

  template <class value_type>
  class ListIterator {
   public:
    Node *node_;
    ListIterator() : node_(nullptr) {}
    ListIterator(Node *node) : node_(node) {}
    ListIterator(const ListIterator &r) : node_(r.node_) {}

    ListIterator &operator=(const ListIterator &r) {
      node_ = r.node_;
      return *this;
    }

    bool operator==(const ListIterator &r) const { return node_ == r.node_; }

    bool operator!=(const ListIterator &r) const { return node_ != r.node_; }

    ListIterator operator++() {
      if (node_) node_ = node_->next_;
      return *this;
    }

    ListIterator operator++(int) {
      ListIterator node_copy = this;
      if (node_) node_ = node_->next_;
      return node_copy;
    }

    ListIterator operator--() {
      if (node_) node_ = node_->prev_;
      return *this;
    }

    ListIterator operator--(int) {
      ListIterator node_copy = this;
      if (node_) node_ = node_->prev_;
      return node_copy;
    }

    T &operator*() const {
      if (!node_) throw std::invalid_argument("Node is null pointer");
      return node_->value_;
    }
  };

  template <class value_type>
  class ListConstIterator {
   public:
    Node *node_;
    ListConstIterator() : node_(nullptr) {}
    ListConstIterator(Node *node) : node_(node) {}
    ListConstIterator(const ListConstIterator &r) : node_(r.node_) {}

    ListConstIterator &operator=(const ListConstIterator &r) {
      node_ = r.node_;
      return *this;
    }

    bool operator==(const ListConstIterator &r) const {
      return node_ == r.node_;
    }

    bool operator!=(const ListConstIterator &r) const {
      return node_ != r.node_;
    }

    ListConstIterator operator++() {
      if (node_) node_ = node_->next_;
      return *this;
    }

    ListConstIterator operator++(int) {
      ListConstIterator node_copy = this;
      if (node_) node_ = node_->next_;
      return node_copy;
    }

    ListConstIterator operator--() {
      if (node_) node_ = node_->prev_;
      return *this;
    }

    ListConstIterator operator--(int) {
      ListConstIterator node_copy = this;
      if (node_) node_ = node_->prev_;
      return node_copy;
    }

    const T &operator*() const {
      if (!node_) throw std::invalid_argument("Node is null pointer");
      return node_->value_;
    }
  };

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using allocator_type = std::allocator<Node>;
  using iterator = ListIterator<value_type>;
  using const_iterator = ListConstIterator<value_type>;

  list() : size_(0) { CreateNode(); }

  list(size_type n) : size_(0) {
    CreateNode();
    try {
      for (size_type i = 0; i < n; i++) insert(end(), value_type{});
    } catch (...) {
      RemoveList();
      throw;
    }
  }

  list(std::initializer_list<value_type> const &items) : size_(0) {
    CreateNode();
    CopyElements(items.begin(), items.end());
  }

  list(const list &l) : size_(0) {
    CreateNode();
    CopyElements(l.cbegin(), l.cend());
  }

  list(list &&l) noexcept : node_(l.node_), size_(l.size_) {
    l.size_ = 0;
    l.node_ = nullptr;
  }

  ~list() { RemoveList(); }

  list &operator=(const list &l) {
    clear();
    CopyElements(l.cbegin(), l.cend());

    return *this;
  }

  list &operator=(list &&l) {
    RemoveList();

    size_ = l.size_;
    node_ = l.node_;

    l.size_ = 0;
    l.node_ = nullptr;

    return *this;
  }

  reference front() { return node_->next_->value_; }

  const_reference front() const { return node_->next_->value_; }

  reference back() { return node_->prev_->value_; }

  const_reference back() const { return node_->prev_->value_; }

  iterator begin() { return iterator(node_->next_); }

  const_iterator cbegin() const { return const_iterator(node_->next_); }

  iterator end() { return iterator(node_); }

  const_iterator cend() const { return const_iterator(node_); }

  bool empty() const { return size_ == 0; }

  size_type size() const { return size_; }

  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(Node) / 2;
  }

  void clear() {
    while (size_ > 0) pop_back();
  }

  iterator insert(iterator pos, const_reference value) {
    Node *node = alloc_.allocate(1);  // Выделение памяти для нового узла
    try {
      // Конструирование объекта с использованием allocator_traits
      std::allocator_traits<decltype(alloc_)>::construct(alloc_, node,
                                                         Node(value));
    } catch (...) {
      alloc_.deallocate(node, 1);  // Освобождение памяти в случае исключения
      throw;
    }

    ChangePointers(node,
                   pos.node_);  // Обновление указателей соседних элементов
    node->prev_->next_ = node->next_->prev_ =
        node;  // Обновление связей нового узла

    ++size_;
    node_->value_ = size();  // Обновление размера списка

    return iterator(node);  // Возврат итератора на вставленный узел
  }

  void erase(iterator pos) {
    if (size_ == 0) return;  // Если список пуст, ничего не делаем
    if (pos == node_) --pos;  // Если позиция указывает на конец, сдвигаем назад

    Node *node = pos.node_;

    ChangePointers(node);  // Обновляем указатели соседних элементов
    --size_;
    node_->value_ = size();

    // Уничтожаем объект с использованием allocator_traits
    std::allocator_traits<decltype(alloc_)>::destroy(alloc_, node);

    // Освобождаем память
    alloc_.deallocate(node, 1);
  }

  void push_back(const_reference value) { insert(end(), value); }

  void pop_back() { erase(end()); }

  void push_front(const_reference value) { insert(begin(), value); }

  void pop_front() { erase(begin()); }

  void swap(list &other) {
    std::swap(this->node_, other.node_);
    std::swap(this->size_, other.size_);
  }

  void merge(list &other) {
    size_type middle = size_;
    iterator middle_it = other.begin();
    splice(cend(), other);
    Merge(begin(), middle_it, 0, middle, size_);
  }

  void splice(const_iterator pos, list &other) {
    pos.node_->prev_->next_ = other.begin().node_;
    other.begin().node_->prev_ = pos.node_->prev_;

    pos.node_->prev_ = (--other.end()).node_;
    (--other.end()).node_->next_ = pos.node_;

    size_ += other.size_;
    node_->value_ = size_;
    other.size_ = 0;
    other.node_->next_ = other.node_->prev_ = other.node_;
  }

  void reverse() {
    Node *node = node_;
    for (size_type i = 0; i < size_ + 1; ++i) {
      std::swap(node->next_, node->prev_);
      node = node->prev_;
    }
  }

  void unique() {
    if (size_ < 1) return;

    iterator prev_it = begin(), curr_it = ++begin();
    for (size_type i = 0, cond = size_; i < cond; ++i) {
      if (prev_it.node_->value_ == curr_it.node_->value_) {
        erase(curr_it);
        curr_it = prev_it.node_->next_;
      } else {
        prev_it = curr_it;
        ++curr_it;
      }
    }
  }

  void sort() { MergeSort(0, size_); }

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    iterator it(pos.node_);
    --pos;
    size_type i = 0;
    try {
      for (auto i : {std::forward<Args>(args)...}) {
        insert(it, i);
        ++i;
      }
    } catch (...) {
      for (; i > 0; --i) pop_back();
    }
    return iterator((++pos).node_);
  }

  template <class... Args>
  void insert_many_back(Args &&...args) {
    insert_many(cend(), args...);
  }

  template <class... Args>
  void insert_many_front(Args &&...args) {
    insert_many(cbegin(), args...);
  }

 private:
  Node *node_;
  size_type size_;
  allocator_type alloc_;

  void CreateNode() {
    node_ = alloc_.allocate(1);  // Выделение памяти для узла
    std::allocator_traits<decltype(alloc_)>::construct(
        alloc_, node_, Node());  // Конструирование узла
    node_->value_ = size();      // Установка значения узла
    node_->prev_ = node_->next_ = node_;  // Установка связей
  }

  void MergeSort(size_type first, size_type last) {
    if (first + 1 == last) return;
    size_type middle = (last + first) / 2;
    MergeSort(first, middle);
    MergeSort(middle, last);

    iterator start(begin()), end(begin());

    for (size_type i = 0; i < first; ++i, ++start);
    for (size_type i = 0; i < middle; ++i, ++end);

    Merge(start, end, first, middle, last);
  }

  void Merge(iterator start, iterator end, size_type first, size_type middle,
             size_type last) {
    Node *node = nullptr;

    for (size_type b = first, e = middle; b < middle && e < last;) {
      if (start.node_->value_ < end.node_->value_) {
        Increase(start.node_, b);
      } else {
        node = end.node_;
        Increase(end.node_, e);
        ChangePointers(node);
        ChangePointers(node, start.node_);
      }
    }
  }

  void ChangePointers(Node *node1, Node *node2) {
    node1->next_ = node2;
    node1->prev_ = node2->prev_;
    node2->prev_ = node2->prev_->next_ = node1;
  }

  void ChangePointers(Node *node) {
    node->prev_->next_ = node->next_;
    node->next_->prev_ = node->prev_;
  }

  void Increase(Node *&node, size_type &count) {
    node = node->next_;
    ++count;
  }

  void RemoveList() {
    clear();  // Очистить список
    std::allocator_traits<decltype(alloc_)>::destroy(
        alloc_, node_);           // Уничтожить объект
    alloc_.deallocate(node_, 1);  // Освободить память
  }

  template <typename Iterable>
  void CopyElements(Iterable begin, Iterable end) {
    try {
      for (auto it = begin; it != end; ++it) insert((*this).end(), *it);
    } catch (...) {
      RemoveList();
      throw;
    }
  }
};
}  // namespace my

#endif  //  my_CONTAINERS_LIST_MY_LIST_H_