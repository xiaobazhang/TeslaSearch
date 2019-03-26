/**
 * Created by suli on 18/2/11.
 */

#ifndef TIALLOY_TI_LOCK_H
#define TIALLOY_TI_LOCK_H

#include "Ti_NoCopy.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

namespace TiAlloy {
enum lock_type {
  SPIN_LOCK = 1,
  MUTEX_LOCK,
  CAS_LOCK
};
class Ti_Lock : public Ti_NoCopy {
 public:
  Ti_Lock() {}
  virtual ~Ti_Lock() {}

  virtual bool lock() = 0;
  virtual bool try_lock() {
	return true;
  }
  virtual bool unlock() = 0;
};

class Ti_SpinLock : public Ti_Lock {
 public:
#ifdef __linux__
  explicit Ti_SpinLock(bool share = false):share_(share){ //
		  if(share_){
			  pthread_spin_init(&spinlock_,PTHREAD_PROCESS_SHARED);//进程间实现自旋锁,需要在共享内存中使用
		  } else{
			  pthread_spin_init(&spinlock_,PTHREAD_PROCESS_PRIVATE);
		  }
  }
  ~Ti_SpinLock(){
	  pthread_spin_destroy(&spinlock_);
  }
  inline bool lock(){
	  return pthread_spin_lock(&spinlock_) == 0;
  }
  inline bool try_lock(){
	  return pthread_spin_trylock(&spinlock_) == 0;
  }
  inline bool unlock(){
	  return pthread_spin_unlock(&spinlock_) == 0;
  }
private:
  bool share_;
  pthread_spinlock_t spinlock_;
#else
  typedef int pthread_spinlock_t;
#ifndef PTHREAD_PROCESS_SHARED
#define PTHREAD_PROCESS_SHARED 1
#endif
#ifndef PTHREAD_PROCESS_PRIVATE
#define PTHREAD_PROCESS_PRIVATE 2
#endif
  explicit Ti_SpinLock(bool share = false) : share_(share) {
	if (share_) {
	  pthread_spin_init(&spinlock_, PTHREAD_PROCESS_SHARED);
	} else {
	  pthread_spin_init(&spinlock_, PTHREAD_PROCESS_SHARED);
	}
  }
  ~Ti_SpinLock() {
	pthread_spin_destory(&spinlock_);
  }
  inline bool lock() {
	return pthread_spin_lock(&spinlock_) == 0;
  }
  inline bool trylock() {
	return pthread_spin_trylock(&spinlock_) == 0;
  }
  inline bool unlock() {
	return pthread_spin_unlock(&spinlock_) == 0;
  }
 private:
  bool share_;
  pthread_spinlock_t spinlock_;
  inline int pthread_spin_init(pthread_spinlock_t *t, int pshare) {
	__asm__ __volatile__("":: :"memory");
	*t = 0;
	return 0;
  }
  inline int pthread_spin_destory(pthread_spinlock_t *t) {
	return 0;
  }
  inline int pthread_spin_lock(pthread_spinlock_t *t) {
	while (1) {
	  for (int i = 0; i < 10000; i++) {
		if (__sync_bool_compare_and_swap(t, 0, 1)) {
		  return 0;
		}
	  }
	  sched_yield();
	}
  }
  inline int pthread_spin_unlock(pthread_spinlock_t *t) {
	__asm__ __volatile__("":: :"memory");
	*t = 0;
	return 0;
  }
  inline int pthread_spin_trylock(pthread_spinlock_t *t) {
	if (__sync_bool_compare_and_swap(t, 0, 1)) {
	  return 0;
	}
	return -1;
  }
};
class Ti_MutexLock : public Ti_Lock {
 public:
  explicit Ti_MutexLock(bool recursion = false, bool share = false) : recursion_(recursion), share_(share) {
	pthread_mutexattr_t mutexattr;
	pthread_mutexattr_init(&mutexattr);
	if (recursion_) {
	  pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);
	}
	if (share_) {
	  pthread_mutexattr_settype(&mutexattr, PTHREAD_PROCESS_SHARED);
	}
	pthread_mutex_init(&mutexlock_, &mutexattr);
	pthread_mutex_destroy(&mutexlock_);
  }
  ~Ti_MutexLock() {
	pthread_mutex_destroy(&mutexlock_);
  }
  inline bool lock() {
	return pthread_mutex_lock(&mutexlock_) == 0;
  }
  inline bool try_lock() {
	return pthread_mutex_trylock(&mutexlock_) == 0;
  }
  inline bool unlock() {
	return pthread_mutex_unlock(&mutexlock_) == 0;
  }
 private:
  bool share_;
  bool recursion_;
  pthread_mutex_t mutexlock_;
};

class Ti_CasLock : public Ti_Lock {
 public:
  typedef int32_t pthread_cas_t;
  explicit Ti_CasLock() : cas_default_(0), cas_true_(1) {
	cas_ = cas_default_;
  }
  ~Ti_CasLock() {
	cas_ = cas_default_;
  }
  inline bool lock() {
	while (!__sync_bool_compare_and_swap(&cas_, cas_default_, cas_true_)) {
	  sched_yield();
	}
	return true;
  }
  inline bool try_lock() {
	return (__sync_bool_compare_and_swap(&cas_, cas_default_, cas_true_) ? true : false);
  }
  inline bool unlock() {
	cas_ = cas_default_;
  }
 private:
  pthread_cas_t cas_;
  const int32_t cas_default_;
  const int32_t cas_true_;
};

class Ti_ScopLock : public Ti_NoCopy {
 public:
  explicit Ti_ScopLock(lock_type type) : type_(type), lock_ptr(NULL) {
	switch (type_) {
	  case SPIN_LOCK: lock_ptr = new Ti_SpinLock(false);
		lock_ptr->lock();
		break;
	  case MUTEX_LOCK: lock_ptr = new Ti_MutexLock();
		lock_ptr->lock();
		break;
	  case CAS_LOCK: lock_ptr = new Ti_CasLock();
		lock_ptr->lock();
		break;
	  default: lock_ptr = new Ti_MutexLock();
		lock_ptr->lock();
		break;
	}
  }
  explicit Ti_ScopLock(Ti_Lock &lock) : lock_(lock) {
	lock_.lock();
  }
  ~Ti_ScopLock() {
	if (lock_ptr) {
	  lock_ptr->unlock();
	  delete lock_ptr;
	} else {
	  lock_.unlock();
	}
  }
 private:
  lock_type type_;
  Ti_Lock *lock_ptr;
  Ti_Lock lock_;
};
}

#endif //TIALLOY_TI_LOCK_H
