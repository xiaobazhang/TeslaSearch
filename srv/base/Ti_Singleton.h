/**
 * Created by suli on 18/2/11.
 */

#ifndef ALGO_TI_SINGLETON_H
#define ALGO_TI_SINGLETON_H

#include <iostream>
#include "Ti_NoCopy.h"
#include "Ti_Lock.h"
namespace TiAlloy {
template<typename T>
class Ti_Singleton : public Ti_NoCopy {
 public:
  Ti_Singleton() : instance_(NULL), exit_relese_(false) {
  }
  ~Ti_Singleton() {
	if (instance_) {
	  delete instance_;
	}
  }
  T *Get() {
	if (instance_ == NULL) {
	  Ti_ScopLock scopLock(SPIN_LOCK);
	  if (instance_ == NULL) {
		instance_ = new T();
	  }
	}
	return instance_;
  }
  T &operator*() {
	return *Get();
  }
  T *operator->() {
	return Get();
  }
 private:
  T *volatile instance_;
  bool exit_relese_;//退出释放
};
}

#endif //ALGO_TI_SINGLETON_H
