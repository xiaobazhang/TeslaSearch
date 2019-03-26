/**
 * Created by suli on 18/2/11.
 */

#ifndef TIALLOY_TI_LOGBUFF_H
#define TIALLOY_TI_LOGBUFF_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

namespace TiAlloy {

class Ti_LogBuff {
 public:
  Ti_LogBuff() : buf_(1024 * 1024) {
	read_index_ = 0;
	write_index_ = 0;
  }
  ~Ti_LogBuff() {}
  int32_t get_write_size() const {
	return write_index_ - read_index_;
  }
  int32_t get_read_size() const {
	return (int32_t) buf_.size() - write_index_;
  }
  void append(const char *buf, int32_t len) {
	std::copy(buf, buf + len, get_write_ptr());
	write_index_ = write_index_ + len;
  }
  char *get_write_ptr() {
	return (&*buf_.begin() + write_index_);
  }
  char *get_read_ptr() {
	return (&*buf_.begin() + read_index_);
  }
 private:
  std::vector<char> buf_;
  int32_t read_index_;
  int32_t write_index_;
};

class LogFile {
 public:
  LogFile(std::string path, int32_t roll_size = 1024 * 1024 * 1024) : roll_size_(roll_size) {
	fill_size_ = 0;
	file_num_ = 0;
	fd_ = -1;
	fd_ = open(path.c_str(), O_WRONLY | O_APPEND | O_CREAT, S_IWUSR);
  }
  ~LogFile() {
	close(fd_);
  }
  void append(const char *s, size_t len) {
	int size = (int) write(fd_, s, len);
	fill_size_ += size;
  }
 private:
  int32_t roll_size_;
  int32_t fill_size_;
  int32_t file_num_;
  int fd_;
};

}

#endif //TIALLOY_TI_LOGBUFF_H
