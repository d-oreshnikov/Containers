#ifndef CONTAINERS_SRC_BITREE_MY_BITREE_H
#define CONTAINERS_SRC_BITREE_MY_BITREE_H

#include <iostream>

#define RED 1
#define BLACK 0

namespace my {

template <typename T, typename T2>
class bitree {
 private:
  typedef struct node {
    T value;       // node key
    T2 value2;     // node value
    node *parent;  // pointer to node parent node
    node *left;    // pointer to node's left node
    node *right;   // pointer to node's right node
    int color;     // node color RED | BLACK
  } node;

  node *root;  // pointer to Red-Black-Tree's root node

  int add_balance(node *);  //  tree balance after add new node
  int del_balance(node *);  //  tree balance after delete node
  int lr(node *);           //  left rotate of tree
  int rr(node *);           //  right rotate of tree
  int rc(node *);           //  recolor of node's

  int add(std::pair<const T, T2>);         // add new node
  int del(const T);                        // del node by key
  node *copy_nodes(const node *src_node);  // rec node coping
  void clear_rec(node *);                  // rec del of RBT

 public:
  // constructors and destructors
  bitree() {  // base constructor for class
    root = nullptr;
    tree_size = 0;
  }

  bitree(const bitree &other) {  // copy condtructor
    root = copy_nodes(other.get_root());
    tree_size = other.get_size();
  }

  ~bitree() { clear(); }

  bitree &operator<<(const std::pair<T, T2> &value) {  // operator <<
    if (!add(value)) {
      ++tree_size;
    }
    return *this;
  }

  bitree &operator<<(std::initializer_list<std::pair<T, T2>>
                         values) {  // operator << for initializer list
    for (const auto &value : values) {
      add(value);
    }
    tree_size += values.size();
    return *this;
  }

  bitree &operator>>(const T &value) {  // operator >> to del node by key
    if (!del(value)) {
      --tree_size;
    }
    return *this;
  }

  template <size_t N>
  bitree &operator>>(
      const T (&values)[N]) {  // operator >> to del mas of nodes by keys
    for (size_t i = 0; i < N; i++) {
      this->operator>>(values[i]);
    }
    return *this;
  }

  bitree &operator=(bitree &&other) noexcept {  // operator = by coping RBT
    if (this != &other) {
      clear();
      root = copy_nodes(other.get_root());
      tree_size = other.tree_size;
    }
    return *this;
  }

  //------------------ITERATOR------------------// Class to iterate in tree
  class tree_iterator {
   private:
    typename bitree<T, T2>::node *root_node;
    int next_node();  // next node
    int back_node();  // prev node
    size_t *max_position;

   public:
    tree_iterator() {};

    tree_iterator(
        const tree_iterator
            &other) {  // copy current_node and postion from another iterator
      current_node = other.current_node;
      position = other.position;
    };
    size_t position = 0;  //  current iterator position in tree
    int first_node();     //  set iterator to min tree node
    int last_node();      //  set iterator to max tree node
    const T &cget() const {
      return current_node->value;
    }  // get node key for read
    T &get() { return current_node->value; }  // get node key for right

    tree_iterator set(const T);  //  set iterator to node

    int initialize(
        typename bitree<T, T2>::node *tree_root,
        size_t *tree_size) {  // init iterator with tree_root and size
                              // if iter pos 0 set it to min node
      root_node = tree_root;
      max_position = tree_size;
      if (position == 0) {
        first_node();
      }
      return 0;
    }

    typename bitree<T, T2>::node
        *current_node;  //  pointer to iterator current node pos

    tree_iterator &operator++() {  //  move iterator to next node
      next_node();
      ++position;
      return *this;
    }

    tree_iterator &operator--() {  //  move iterator to prev node
      back_node();
      --position;
      return *this;
    }

    tree_iterator &operator=(
        tree_iterator &other) {  // copy one node in another by iterator
      this->position = other.position;
      this->current_node = other.current_node;
      this->root_node = other.root_node;
      this->max_position = other.max_position;
      return *this;
    }

    bool operator!=(
        tree_iterator other) {  // return true if iterators pos are diff
      if (this->position == other.position) {
        return false;
      }
      return true;
    }

    bool operator==(const tree_iterator other) const {
      return current_node == other.current_node &&
             position == other.position;  // return true if iterators pos are ==
    }
  };  // class tree_iterator

  size_t tree_size;              //  current tree size
  void clear();                  // clean all nodes
  const node *get_root() const;  // return pointer to tree root node
  void set_root(node *);         // set tree root node

  void move(const bitree &other);  //  move one tree to another
  size_t get_size() const;         // get tree size

  T2 &find_value(T);  // return node by key

  tree_iterator begin();  //  return iterator to start of tree
  tree_iterator end();    //   return iterator to end of tree
};  // class bitree

//------------------FUNCTIONS------------------//
//------------------ADD/DEL------------------//
template <typename T, typename T2>
int bitree<T, T2>::add(
    std::pair<const T, T2>
        value) {  // add new node to tree and make balance if nes
  node *current, *parent, *new_node;
  current = root;
  parent = nullptr;

  while (current != nullptr) {
    parent = current;
    current = value.first < current->value
                  ? current->left
                  : current->right;  // find place to new node, goes to right or
                                     // left branch
  }
  new_node = new node;  // makes new node on finded place
  new_node->value = value.first;
  new_node->value2 = value.second;
  new_node->parent = parent;
  new_node->left = nullptr;
  new_node->right = nullptr;
  new_node->color = RED;

  if (parent) {  //  Binding a new node to a tree
    if (value.first < parent->value)
      parent->left = new_node;
    else
      parent->right = new_node;
  } else {
    root = new_node;
  }
  add_balance(new_node);  // make balance to make from bintree RBT
  return 0;
}

template <typename T, typename T2>
int bitree<T, T2>::del(const T value) {
  node *x = nullptr;
  node *y, *z = root;
  while (z != nullptr)
    if (value == z->value)
      break;
    else
      z = value < z->value ? z->left : z->right;

  if (!z || z == nullptr) return 1;
  if (z->left == nullptr || z->right == nullptr) {
    y = z;
  } else {
    y = z->right;
    while (y->left != nullptr) y = y->left;
  }
  if (y->right != nullptr) {
    x = y->right;
    x->parent = y->parent;
  }
  if (x && y->parent)
    if (y == y->parent->left)
      y->parent->left = x;
    else
      y->parent->right = x;
  else
    root = x;
  if (y != z) z->value = y->value;
  if (y->color == BLACK) del_balance(x);
  if (y->parent && y->parent->right == y) y->parent->right = nullptr;
  if (y->parent && y->parent->left == y) y->parent->left = nullptr;
  delete (y);
  return 0;
}

//------------------BALANCE------------------//
template <typename T, typename T2>
int bitree<T, T2>::add_balance(node *nd) {
  while (nd != root && nd->parent->color == RED) {
    if (nd->parent ==
        nd->parent->parent
            ->left) {  // If the parent of the node is the left child
      node *uncle = nd->parent->parent->right;
      if (uncle && uncle->color == RED) {  // If "uncle" exists and red
        rc(nd->parent->parent);
        nd = nd->parent->parent;
      } else {
        if (nd == nd->parent->right) {
          nd = nd->parent;
          lr(nd);
        }
        nd->parent->color = BLACK;  // If the "uncle" is black
        nd->parent->parent->color = RED;
        rr(nd->parent->parent);
      }
    } else {  // If the parent of the node is the right child
      node *uncle = nd->parent->parent->left;
      if (uncle && uncle->color == RED) {
        rc(nd->parent->parent);
        nd = nd->parent->parent;
      } else {
        if (nd == nd->parent->left) {
          nd = nd->parent;
          rr(nd);
        }
        nd->parent->color = BLACK;
        nd->parent->parent->color = RED;
        lr(nd->parent->parent);
      }
    }
  }
  root->color = BLACK;
  return 0;
}

template <typename T, typename T2>
int bitree<T, T2>::del_balance(node *nd) {
  while (nd != root && nd->color == BLACK) {
    if (nd == nd->parent->left) {  // If nd is the left child of its parent
      node *brother = nd->parent->right;
      if (brother->color == RED) {  // Case 1: Brother Red
        brother->color = BLACK;
        nd->parent->color = RED;
        lr(nd->parent);
        brother = nd->parent->right;
      }
      if (brother->left->color == BLACK &&
          brother->right->color ==
              BLACK) {  // Case 2: The brother has both children black
        brother->color = RED;
        nd = nd->parent;
      } else {
        if (brother->right->color ==
            BLACK) {  // Case 3: The brother's right child is black, and the
                      // left one is red
          brother->left->color = BLACK;
          brother->color = RED;
          rr(brother);
          brother = nd->parent->right;
        }
        brother->color =
            nd->parent->color;  // Case 4: The brother's right child is red
        nd->parent->color = BLACK;
        brother->right->color = BLACK;
        lr(nd->parent);
        nd = root;
      }
    } else {  // If nd is the right child, the logic is symmetric as described
              // above ("left" and "right" are replaced)
      node *brother = nd->parent->left;
      if (brother->color == RED) {
        brother->color = BLACK;
        nd->parent->color = RED;
        rr(nd->parent);
        brother = nd->parent->left;
      }
      if (brother->right->color == BLACK && brother->left->color == BLACK) {
        brother->color = RED;
        nd = nd->parent;
      } else {
        if (brother->left->color == BLACK) {
          brother->right->color = BLACK;
          brother->color = RED;
          lr(brother);
          brother = nd->parent->left;
        }
        brother->color = nd->parent->color;
        nd->parent->color = BLACK;
        brother->left->color = BLACK;
        rr(nd->parent);
        nd = root;
      }
    }
  }
  nd->color = BLACK;  // Completing the balancing: the nd node is repainted
                      // black to restore the properties of the tree.
  return 0;
}

//------------------TREE_MOVE------------------//
template <typename T, typename T2>
int bitree<T, T2>::rc(node *nd) {  // It is used to restore the "red node has
                                   // black children" property.
  nd->left->color = BLACK;
  nd->right->color = BLACK;
  nd->color = RED;
  return 0;
}

template <typename T, typename T2>
int bitree<T, T2>::lr(node *nd) {  // left rotation
  node *pNode = nd;
  node *cNode = nd->right;
  if (!cNode) return 1;
  pNode->right = cNode->left;
  if (cNode->left != nullptr) cNode->left->parent = pNode;
  if (cNode != nullptr) cNode->parent = pNode->parent;
  if (pNode->parent) {
    if (pNode == pNode->parent->left)
      pNode->parent->left = cNode;
    else
      pNode->parent->right = cNode;
  } else {
    root = cNode;
  }
  cNode->left = pNode;
  if (pNode != nullptr) pNode->parent = cNode;
  return 0;
}

template <typename T, typename T2>
int bitree<T, T2>::rr(node *nd) {  // right rotation
  node *pNode = nd;
  node *cNode = nd->left;
  if (!cNode) return 1;
  pNode->left = cNode->right;
  if (cNode->right != nullptr) cNode->right->parent = pNode;
  if (cNode != nullptr) cNode->parent = pNode->parent;
  if (pNode->parent) {
    if (pNode == pNode->parent->right)
      pNode->parent->right = cNode;
    else
      pNode->parent->left = cNode;
  } else {
    root = cNode;
  }
  cNode->right = pNode;
  if (pNode != nullptr) pNode->parent = cNode;
  return 0;
}
//------------------HELP_FUNCS------------------//
template <typename T, typename T2>
void bitree<T, T2>::clear_rec(node *tmp) {  // Deleting nodes recursively
  if (tmp != nullptr && tree_size != 0) {
    node *left = tmp->left;
    node *right = tmp->right;
    delete tmp;
    --tree_size;
    clear_rec(left);
    clear_rec(right);
  }
}

template <typename T, typename T2>
void bitree<T, T2>::clear() {  // del tree
  clear_rec(root);
  tree_size = 0;
  root = nullptr;
}

template <typename T, typename T2>
const typename bitree<T, T2>::node *bitree<T, T2>::get_root()
    const {  // return tree root
  return root;
}

template <typename T, typename T2>
T2 &bitree<T, T2>::find_value(T value) {
  node *iter = root;
  while (iter != nullptr) {
    if (value == iter->value) {
      return iter->value2;
    } else {
      iter = value < iter->value ? iter->left : iter->right;
    }
  }
  throw std::out_of_range("Key not found");
}

template <typename T, typename T2>
void bitree<T, T2>::move(const bitree &other) {
  root = other.get_root();
  tree_size = other.get_size();
  other.set_root(nullptr);
}

template <typename T, typename T2>
size_t bitree<T, T2>::get_size() const {
  return tree_size;
}

template <typename T, typename T2>
typename bitree<T, T2>::node *bitree<T, T2>::copy_nodes(
    const typename bitree<T, T2>::node *src_node) {
  if (!src_node) {
    return nullptr;
  }
  typename bitree<T, T2>::node *new_node = new node;
  new_node->value = src_node->value;
  new_node->value2 = src_node->value2;
  new_node->parent = nullptr;
  new_node->left = nullptr;
  new_node->right = nullptr;
  new_node->color = src_node->color;

  new_node->left = copy_nodes(src_node->left);
  new_node->right = copy_nodes(src_node->right);

  return new_node;
}

template <typename T, typename T2>
typename bitree<T, T2>::tree_iterator bitree<T, T2>::begin() {
  tree_iterator iter;
  iter.initialize(root, &tree_size);
  iter.first_node();
  return iter;
}

template <typename T, typename T2>
typename bitree<T, T2>::tree_iterator bitree<T, T2>::end() {
  tree_iterator iter;
  iter.initialize(root, &tree_size);
  iter.last_node();
  return iter;
}

//------------------ITER_FUNCS------------------//
template <typename T, typename T2>
int bitree<T, T2>::tree_iterator::first_node() {
  current_node = root_node;
  position = 0;
  while (current_node->left != nullptr) current_node = current_node->left;
  return 0;
}

template <typename T, typename T2>
int bitree<T, T2>::tree_iterator::last_node() {
  current_node = root_node;
  position = *max_position;
  while (current_node->right != nullptr) current_node = current_node->right;
  return 0;
}

template <typename T, typename T2>
int bitree<T, T2>::tree_iterator::next_node() {
  if (current_node->right != nullptr) {
    current_node = current_node->right;
    while (current_node->left != nullptr) current_node = current_node->left;
  } else if (current_node == current_node->parent->left)
    current_node = current_node->parent;
  else if (current_node == current_node->parent->right) {
    while (current_node != root_node &&
           current_node == current_node->parent->right)
      current_node = current_node->parent;
    if (current_node != root_node)
      current_node = current_node->parent;
    else
      first_node();
  } else
    return 1;
  return 0;
}

template <typename T, typename T2>
int bitree<T, T2>::tree_iterator::back_node() {
  tree_iterator it;
  if (position == 1) {
    position = *max_position;
    last_node();
  } else {
    it.initialize(root_node, max_position);
    it.first_node();
    for (size_t i = 0; i < position - 1; i++) ++it;
    position = it.position;
    current_node = it.current_node;
  }
  return 0;
}

template <typename T, typename T2>
typename bitree<T, T2>::tree_iterator bitree<T, T2>::tree_iterator::set(
    const T value) {
  tree_iterator it;
  it.initialize(root_node, max_position);
  it.first_node();
  while (it.position < *max_position + 1) {
    if (it.cget() == value) return it;
    ++it;
  }
  return it;
}

}  // namespace my

#endif  // CONTAINERS_SRC_BITREE_MY_BITREE_H
