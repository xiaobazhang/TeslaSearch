/**
 * Created by suli on 18/2/28.
 */

#ifndef TIALLOY_TI_HASHFUN_H
#define TIALLOY_TI_HASHFUN_H
#include <iostream>
#include <stdint.h>
#include <string>

using namespace std;
namespace TiAlloy {
static u_int32_t add_hash(void *key, int32_t len) {
	u_char *p = static_cast<u_char *>(key);
	u_int32_t h = 0;
	for (int32_t i = 0; i < len; i++) {
		h += p[i];
	}
	return h;
}
static u_int32_t xor_hash(void *key, int32_t len) {
	u_char *p = static_cast<u_char *>(key);
	u_int32_t h = 0;
	for (int32_t i = 0; i < len; i++) {
		h ^= p[i];
	}
}
class HashFun {
 public:
	u_int32_t operator()(const string &key) {
		return TiAlloy::add_hash((void *) key.c_str(), (int32_t) key.size());
	}
};
class HashEqual {
 public:
	bool operator()(const string &a, const string &b) {
		return (a == b);
	}
};

}

#endif //TIALLOY_TI_HASHFUN_H
