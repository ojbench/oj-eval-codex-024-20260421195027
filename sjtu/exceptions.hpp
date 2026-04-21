#ifndef SJTU_EXCEPTIONS_HPP
#define SJTU_EXCEPTIONS_HPP

#include <exception>
#include <string>

namespace sjtu {

class exception : public std::exception {
protected:
  std::string msg;

public:
  exception() = default;
  explicit exception(std::string m) : msg(std::move(m)) {}
  const char *what() const noexcept override { return msg.c_str(); }
};

class index_out_of_bound : public exception {
public:
  index_out_of_bound() : exception("index_out_of_bound") {}
};

class runtime_error : public exception {
public:
  runtime_error() : exception("runtime_error") {}
};

class invalid_iterator : public exception {
public:
  invalid_iterator() : exception("invalid_iterator") {}
};

class container_is_empty : public exception {
public:
  container_is_empty() : exception("container_is_empty") {}
};
} // namespace sjtu

#endif

