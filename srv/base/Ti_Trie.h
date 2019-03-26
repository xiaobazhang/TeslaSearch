/**
 * Created by suli on 18/2/26.
 */

#ifndef TIALLOY_TI_TRIE_H
#define TIALLOY_TI_TRIE_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;
namespace TiAlloy {
const int32_t SIZE = 26;
class trie_node {
 public:
  trie_node() : count(0), is_word(false) {
	for (int i = 0; i < SIZE; i++) {
	  child[i] = NULL;
	}
  }
  int32_t count;
  trie_node *child[SIZE];
  bool is_word;
};

class Ti_Trie {
 public:
  Ti_Trie() {
	root = create_node();
  }
  ~Ti_Trie() {
	for (int i = 0; i < l.size(); i++) {
	  delete l[i];
	}
  }
  bool insert_node(const char *n) {
	const char *p = n;
	trie_node *node = root;
	while (*p) {
	  printf("%c", *p);
	  int32_t id = *p - 'a';
	  if (node->child[id] == NULL) {
		node->child[id] = create_node();
	  }
	  node = node->child[id];
	  node->count++;
	  p++;
	}
	printf("\n");
	node->is_word = true;
	return true;
  }
  int search_word(const char *w) {
	const char *p = w;
	trie_node *t = root;
	while (*p) {
	  t = t->child[*p - 'a'];
	  p++;
	  if (t == NULL) {
		return 0;
	  }
	}
	printf("%d\n", t->count);
	return t->count;
  }
 private:
  trie_node *root;
  std::vector<trie_node *> l;
  trie_node *create_node() {
	trie_node *r = new trie_node();
	l.push_back(r);
	r->count = 0;
	return r;
  }
};
}

#endif //TIALLOY_TI_TRIE_H
