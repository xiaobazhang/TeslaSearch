/**
 * Created by suli on 18/1/27.
 */

#ifndef ALGO_BASE_LIST_H
#define ALGO_BASE_LIST_H
#include <iostream>

namespace TiAlloy {

template<typename T>
struct Node {
  Node(T data) {
	value = data;
	pre = NULL;
	next = NULL;
  }
  T value;
  Node *pre;
  Node *next;
};
/*
 *模板参数T,T的引用,T的指针
 */
template<typename T, typename Ref, typename Ptr>
class List_Iterator {
  typedef Node<T> __node;
  typedef List_Iterator<T, Ref, Ptr> self;
 public:
  List_Iterator() {}
  List_Iterator(__node *n) : node(n) {}
  ~List_Iterator() {}

  Ref operator*() const {
	return node->value;
  }
  Ref operator->() const {
	return &(operator*());
  }

  bool operator==(const self &n) const {
	return (n.node == node);
  }
  bool operator!=(const self &n) const {
	return (n.node != node);
  }

  self &operator++() {  //前置++
	node = node->next;
	return *this;
  }

  self &operator++(int) {   //后置++
	self tmp(*this);
	operator++();
	return tmp;
  }

  self &operator--() {
	node = node->pre;
	return *this;
  }

  self &operator--(int) {
	self tmp(*this);
	operator--();
	return tmp;
  }
  bool swap(self &a, self &b) {
	T c = a.node->value;
	a.node->value = b.node->value;
	b.node->value = c;
	return true;
  }

 private:
  __node *node;

};

template<class T>
class List {
 public:
  typedef List_Iterator<T, T &, T *> iterator;
  List() : head(NULL), len(0) {
  }
  List(T &value) : head(NULL), len(0) {
	push_back(value);
  }
  List(T value) : head(NULL), len(0) {
	push_back(value);
  }
  ~List() {
	Node<T> *tmp = head;
	while (tmp) {
	  delete tmp;
	  tmp = tmp->next;
	  if (tmp == head) {
		break;
	  }
	}
  }
  bool push_back(const T &value) {
	Node<T> *tmp = new Node<T>(value);
	if (head == NULL) {
	  head = tmp;
	  head->pre = tmp;
	} else {
	  tmp->pre = head->pre; //新节点的前一个是尾节点
	  head->pre->next = tmp;
	  head->pre = tmp;
	}
	len++;
	return true;
  }
  bool push_back(T &value) {
	Node<T> *tmp = new Node<T>(value);
	if (head == NULL) {
	  head = tmp;
	  head->pre = tmp;
	} else {
	  tmp->pre = head->pre; //新节点的前一个是尾节点
	  head->pre->next = tmp;
	  head->pre = tmp;
	}
	len++;
	return true;
  }
  bool push_front(const T &value) {
	Node<T> *t = new Node<T>(value);
	if (head == NULL) {
	  head = t;
	  head->pre = t;
	} else {
	  t->pre = head;
	  t->next = head->next;
	  head->next = t;
	  if (t->next) {
		t->next->pre = t;
	  }
	}
	len++;
	return true;
  }
  bool push_front(T &value) {
	Node<T> *t = new Node<T>(value);
	if (head == NULL) {
	  head = t;
	  head->pre = t;
	} else {
	  t->pre = head;
	  t->next = head->next;
	  head->next = t;
	  if (t->next) {
		t->next->pre = t;
	  }
	}
	len++;
	return true;
  }
  Node<T> *find(T &value) {
	Node<T> *tmp = head;
	while (tmp) {
	  if (tmp->value == value) {
		return tmp;
	  }
	  tmp = tmp->next;
	}
	return NULL;
  }
  bool remove(T &value) {
	Node<T> *tmp = find(value);
	if (tmp) {
	  tmp->pre->next = tmp->next;
	  tmp->next->pre = tmp->pre;
	  len--;
	  delete tmp;
	  return true;
	} else {
	  std::cout << "no this node!!" << std::endl;
	}
	return true;
  }
  int size() const {
	return len;
  }
  bool clear() {
	Node<T> *tmp = head;
	while (tmp) {
	  delete tmp;
	  tmp = tmp->next;
	  if (tmp == head) {
		break;
	  }
	}
	head = NULL;
	len = 0;
	return true;
  }
  void pri() {
	Node<T> *tmp = head->next;
	while (tmp != head) {
	  std::cout << "pri value=" << tmp->value << std::endl;
	  tmp = tmp->pre;
	}
  }
  bool reverse() {
	Node<T> *h = head;
	Node<T> *t = head->pre;
	head = head->pre;
	while (h) {
	  Node<T> *n = h->next;
	  h->next = h->pre;
	  h->pre = n;
	  std::cout << "reverse=" << h->value << std::endl;
	  if (h == t) {
		break;
	  }
	  h = n;
	}
	return true;
  }

  T operator[](int index) {
	if (index < 0) {
	  T tmp;
	  return tmp;
	}
	Node<T> *tmp = head;
	for (int i = 0; i < index; i++) {
	  if (tmp) {
		tmp = tmp->next;
	  } else {
		T t;
		return t;
	  }
	}
	return tmp->value;
  }
  iterator begin() {
	return iterator(head);
  }
  iterator end() {
	return iterator(head->pre);
  }
 private:
  int len;
  Node<T> *head;
};

}

#endif //ALGO_BASE_LIST_H
