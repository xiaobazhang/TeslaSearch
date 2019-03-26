/**
 * Created by suli on 18/3/1.
 */

#ifndef TIALLOY_TI_REFLECT_H
#define TIALLOY_TI_REFLECT_H
#include <iostream>
#include <map>

using namespace std;
namespace TiAlloy {
class ReflectObject {
 public:
  ReflectObject() {}
  ~ReflectObject() {}
  virtual bool global_init() { return true; }
  virtual bool init() { return true; }
  virtual ReflectObject *new_instance() = 0;
};

class Reflect {
 public:
  Reflect() {};
  ~Reflect() {};
  void register_object(ReflectObject *ob);
  ReflectObject *get_instance(const string &name);
  ReflectObject *get_instance(const char *name);
 private:
  std::map<string, ReflectObject *> object_map;
};
}

#endif //TIALLOY_TI_REFLECT_H
