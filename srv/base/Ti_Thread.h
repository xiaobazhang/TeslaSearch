/**
 * Created by suli on 18/2/11.
 */

#ifndef TIALLOY_TI_THREAD_H
#define TIALLOY_TI_THREAD_H

#include <pthread.h>
#include <iostream>
#include "Ti_NoCopy.h"

namespace TiAlloy {
class Ti_Thread;
//线程工作入口函数
static void *thread_work(void *task) {
  if (task == NULL) {
	return NULL;
  }
  Ti_Thread *thread = (Ti_Thread *) task;
  thread->trigger_thread_create_enent();
  thread->run();
  thread->trigger_thread_exit_enent();
  return thread;
}
class Ti_Runnable : public Ti_NoCopy {
 public:
  Ti_Runnable() {}
  virtual ~Ti_Runnable() {}
 public:
  virtual void run() = 0;
};

class Ti_ThreadEventListener : public Ti_NoCopy {
 public:
  Ti_ThreadEventListener() {}
  virtual ~Ti_ThreadEventListener() {}

  virtual void thread_create_handle() = 0;

  virtual void thread_exit_handle() = 0;
};

class Ti_Thread : public Ti_Runnable {
 public:
  explicit Ti_Thread(bool delete_runnable = false,
					 bool delete_listener = false,
					 Ti_Runnable *runnable)
	  : delete_runnable_(delete_runnable),
		delete_listener_(delete_listener),
		ti_runnable_(runnable),
		listener_(NULL),
		stack_size_(1024 * 1024 * 2) {
  }
  Ti_Thread() : delete_runnable_(false),
				delete_listener_(false),
				ti_runnable_(NULL),
				listener_(NULL),
				stack_size_(1024 * 1024 * 2) {
  }
  ~Ti_Thread() {
  }
  void run() {
	if (ti_runnable_) {
	  ti_runnable_->run();
	  if (delete_runnable_) {
		delete ti_runnable_;
		ti_runnable_ = NULL;
	  }
	  if (delete_listener_ && listener_) {
		delete listener_;
		listener_ = NULL;
	  }
	}
  }
  void start() {
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, stack_size_);
	if (pthread_create(&thread_, &attr, thread_work, (void *) this) != 0) {
	  std::cout << "create thread faild!!" << std::endl;
	}
	pthread_attr_destroy(&attr);
  }
  void join() {
	pthread_join(thread_, NULL);
  }
  void set_thread_stack_size(int32_t size) {
	if (size < 1024 * 1024) {
	  stack_size_ = 1024 * 1024;
	}
	stack_size_ = size;
  }
  void trigger_thread_create_enent() {
	if (listener_) {
	  listener_->thread_create_handle();
	}
  }
  void trigger_thread_exit_enent() {
	if (listener_) {
	  listener_->thread_exit_handle();
	}
  }
 private:
  bool delete_runnable_;
  bool delete_listener_;
  Ti_Runnable *ti_runnable_;
  Ti_ThreadEventListener *listener_;
  pthread_t thread_;
  int32_t stack_size_;
};
}

#endif //TIALLOY_TI_THREAD_H
