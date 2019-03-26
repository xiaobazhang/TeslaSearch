/**
 * Created by suli on 18/2/27.
 */

#ifndef TIALLOY_TI_HASHMAP_H
#define TIALLOY_TI_HASHMAP_H
#include <iostream>
#include <stdint.h>

namespace TiAlloy {

const int32_t PSIZE = 28;
static int32_t prime[PSIZE] = {
	57, 97, 193, 389, 769,
	1543, 3079, 6151, 12289, 24593,
	49157, 98317, 196613, 393241, 786433,
	1572869, 3145739, 6291469, 12582917, 25165843,
	50331653, 100663319, 201326611, 402653189, 805306457,
	1610612741
};

class HashMapUtil {
 public:
  static int find_next_prime_num(int current) {
	for (int i = 0; i < PSIZE; i++) {
	  if (current < prime[i]) {
		return prime[i];
	  }
	}
	return prime[PSIZE - 1];
  }
};

template<typename Key, typename Value, typename HashFun, typename EqualKey>
class Ti_HashMap {
 private:
  template<typename Key_, typename Value_>
  class MapNode {
   public:
	Key_ key;
	Value_ value;
	bool used;
	MapNode *next;
	MapNode *pre;
   public:
	MapNode() : used(false), next(NULL) {}
	MapNode(const MapNode &n) {
	  key = n.key;
	  value = n.value;
	  used = n.used;
	  next = NULL;
	  pre = NULL;
	}
	MapNode &operator=(const MapNode &n) {
	  key = n.key;
	  value = n.value;
	  used = n.used;
	  next = n.next;
	  pre = n.pre;
	  return *this;
	}
	~MapNode() {}
  };
 public:
  typedef MapNode<Key, Value> Node;
  Ti_HashMap() : table(NULL), loading_factor(0.9) {
	hash = HashFun();
	equal = EqualKey();
	hashMapUtil = HashMapUtil();
	capacity = hashMapUtil.find_next_prime_num(0);
	table = new Node[capacity + 1];//创建新的哈希表
	for (int i = 0; i < capacity; i++) {
	  table[i].used = false;
	  table[i].next = table[i].pre = NULL;
	}
	size = 0;
  }
  ~Ti_HashMap() {
	delete_node(table, capacity);
  }
  bool insert(const Key &k, const Value &v) {
	int32_t index = hash(k) % capacity;
	if (!table[index].used) {
	  table[index].used = true;
	  table[index].key = k;
	  table[index].value = v;
	  size++;
	  return true;
	} else {
	  if (table[index].key == k) {
		table[index].value = v;
		return true;
	  }
	}
	Node *t = table[index].next;
	while (t) {
	  if (!t->used) {//位置没用
		table[index].used = true;
		table[index].key = k;
		table[index].value = v;
		size++;
		return true;
	  } else {
		if (t->key == k) { //如果只是同一个Key进行修改
		  table[index].value = v;
		  return true;
		} else {//不是同一个key
		  t = t->next;
		}
	  }
	}
	Node *tmp = new Node();
	tmp->used = true;
	tmp->key = k;
	tmp->value = v;
	tmp->pre = t;
	size++;
	t->next = tmp;//链表节点加上冲突节点
	if (size > capacity * loading_factor) {
	  rehash();
	}
	return true;
  }
  bool rehash() {
	int32_t old_capacity = capacity;
	capacity = hashMapUtil.find_next_prime_num(size);
	Node *t_table = new Node[capacity + 1];
	for (int i = 0; i < capacity; i++) {
	  table[i].used = false;
	  table[i].next = table[i].pre = NULL;
	}
	Node *t = table;
	table = t_table;
	for (int i = 0; i < old_capacity; i++) {
	  Node *tmp = &t[i];
	  while (tmp) {
		insert(tmp->key, tmp->value);
		tmp = tmp->next;
	  }
	}
	delete_node(t, old_capacity);
	return true;
  }
  bool remove(const Key &k) {
	int32_t index = hash(k) % capacity;
	if (table[index].used && table[index].key == k) {
	  table[index].used = false;
	  size--;
	  return true;
	}
	Node *t = table[index].next;//拿到链表
	while (t) {
	  if (t->used && t->key == k) { //找到应该删除节点
		t->pre->next = t->next;
		t->next->pre = t->pre;
		delete t;
		return true;
	  }
	  t = t->next;
	}
	return true;
  }
  Value &find(const Key &k) {
	int32_t index = hash(k) % capacity;
	if (table[index].used && table[index].key == k) {
	  return table[index].value;
	}
	Node *t = table[index].next;
	while (t) {
	  if (t->used && t->key == k) {
		return t->value;
	  }
	  t = t->next;
	}
	return table[capacity].value;
  }
  const Value &operator[](const Key &k) const {
	return find(k);
  }
  Value &operator[](const Key &k) {
	return find(k);
  }
 protected:
  void delete_node(Node *t, int32_t cap) {
	for (int i = 0; i < cap; i++) {
	  Node *tmp = t[i].next;
	  while (tmp) {
		Node *p = tmp->next;
		delete tmp;
		tmp = p;
	  }
	}
	delete[] t;
  }
 private:
  HashFun hash;
  EqualKey equal;
  HashMapUtil hashMapUtil;
  Node *table;
  int32_t size;
  int32_t capacity;
  const float loading_factor;
};

}
#endif //TIALLOY_TI_HASHMAP_H
