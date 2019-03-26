/**
 * Created by suli on 18/2/4.
 */

#ifndef TIALLOY_TI_STRING_H
#define TIALLOY_TI_STRING_H

#include <iostream>

namespace TiAlloy {
class Test {
 public:
  Test &d;
};
struct name {
  char c;
  short b;
  int a;

};
class String {
 public:
  String() {
	s = new char[1];
	len = 0;
  }
  ~String() {
	delete[]s;
  }
  String(String &str) {
	char *p = new char[str.len + 1];
	memset(p, 0, str.len + 1);
	memcpy(p, str.s, str.len);
	len = str.len;
	s = p;
  }
  String(const char *str) {
	if (str != NULL) {
	  char *p = new char[strlen(str) + 1];
	  strcpy(p, str);
	  s = p;
	  len = strlen(str);
	}
  }

  String &operator=(const String &str) {
	if (s = str.s) {
	  return *this;
	}
	if (s) {
	  delete[]s;
	}
	char *p = new char[str.len + 1];
	memset(p, 0, str.len + 1);
	memcpy(p, str.s, str.len);
	s = p;
	len = str.len;
	return *this;
  }
  const char *c_str() {
	return s;
  }
  bool operator==(String &str) {
	return (strcmp(s, str.s) == 0);
  }
  int length() {
	return len;
  }
  char operator[](int ix) {
	if (ix > len && ix < 0) {
	  printf("error");
	}
	return s[ix];
  }
 private:
  char *s;
  int len;
};
}

#endif //TIALLOY_TI_STRING_H
