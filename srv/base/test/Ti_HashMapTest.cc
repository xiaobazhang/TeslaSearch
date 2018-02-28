/**
 * Created by suli on 18/2/28.
 */

#include "../Ti_HashMap.h"
#include "../Ti_HashFun.h"
#include "Ti_Test.h"

using namespace TiAlloy;

void HashMap_Test() {
	Ti_HashMap<string, string, HashFun, HashEqual> map;
	map.insert("hello", "12345");
	map.insert("ni", "12");
	map.insert("hao", "34");
	map.insert("wo", "56");
	map.insert("xiao", "78");
	map.insert("ba", "90");
	std::cout << map["hello"] << ":" << map["ba"] << std::endl;
	map["hello"] = "432";
	map.remove("ba");
	std::cout << map["hello"] << map["ba"] << std::endl;
}

