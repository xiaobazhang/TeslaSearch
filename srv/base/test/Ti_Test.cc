/**
 * Created by suli on 18/1/27.
 */

#include "../Ti_List.h"
#include "../Ti_Tree.h"
#include "../Ti_Sort.h"
#include "../Ti_Trie.h"

using namespace TiAlloy;

void Tree_Test() {
	BinaryTree<int, TreeEqual> tree;
	std::vector<int> vec;
	for (int i = 0; i < 10; i++) {
		int tmp = rand() % (100);
		std::cout << tmp << std::endl;
		tree.insert(tmp);
	}
	tree.print_tree(PRE_ORDER);
	tree.print_tree(IN_ORDER);
	tree.print_tree(POST_ORDER);

	std::vector<int> tmp;
	tree.find_rang(10, 50, tmp);
	for (int i = 0; i < tmp.size(); i++) {
		std::cout << tmp[i] << std::endl;
	}

}
void List_Test() {
	List<int> test;
	for (int i = 0; i < 10; i++) {
		test.push_back(i);
		printf("size=%d\n", test.size());
	}
	for (int i = 0; i < test.size(); i++) {
		printf("value=%d\n", test[i]);
	}
	test.reverse();
	test.pri();
	List<int>::iterator iter = test.begin();
	for (; iter != test.end(); iter++) {
		printf("iter value=%d\n", *iter);
	}
	for (int i = 0; i < test.size(); i++) {
		printf("invert value=%d\n", test[i]);
	}
	test.clear();
	printf("size = %d\n", test.size());
}

void Sort_Test() {
	std::vector<int> tmp;
	for (int i = 0; i < 50; i++) {
		int t = rand() % (100);
		std::cout << t << ",";
		tmp.push_back(t);
	}
	std::cout << std::endl;
	TiAlloy::sort<int, Equal>(tmp, HEADP_SORT);
	for (int i = 0; i < tmp.size(); i++) {
		std::cout << tmp[i] << ",";
	}
	std::cout << std::endl;
}

void Trie_Test() {
	std::vector<std::string> t;
	t.push_back("abcd");
	t.push_back("cdfrqwer");
	t.push_back("cdefsdfg");
	Ti_Trie trie;
	for (int i = 0; i < t.size(); i++) {
		trie.insert_node(t[i].c_str());
	}
	if (trie.search_word("abcd")) {
		std::cout << "abcd" << std::endl;
	} else {
		std::cout << "have no abcd!!" << std::endl;
	}
}




