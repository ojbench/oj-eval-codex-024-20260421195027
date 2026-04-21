#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include <deque>
#include <cstddef>
#include <iterator>
#if defined(__has_include)
#  if __has_include("exceptions.hpp")
#    include "exceptions.hpp"
#  else
#    include "sjtu/exceptions.hpp"
#  endif
#else
#  include "sjtu/exceptions.hpp"
#endif

namespace sjtu {

template <class T>
class deque {
  using base_t = std::deque<T>;
  base_t d;

public:
  class const_iterator;
  class iterator {
    friend class deque;
    friend class const_iterator;
    deque *owner{};
    typename base_t::iterator it;

    iterator(deque *o, typename base_t::iterator i) : owner(o), it(i) {}

  public:
    iterator() = default;
    iterator operator+(const int &n) const { return iterator(owner, it + n); }
    iterator operator-(const int &n) const { return iterator(owner, it - n); }
    int operator-(const iterator &rhs) const {
      if (owner != rhs.owner) throw invalid_iterator();
      return static_cast<int>(it - rhs.it);
    }
    iterator &operator+=(const int &n) {
      it += n;
      return *this;
    }
    iterator &operator-=(const int &n) {
      it -= n;
      return *this;
    }
    iterator operator++(int) {
      iterator tmp = *this;
      ++it;
      return tmp;
    }
    iterator &operator++() {
      ++it;
      return *this;
    }
    iterator operator--(int) {
      iterator tmp = *this;
      --it;
      return tmp;
    }
    iterator &operator--() {
      --it;
      return *this;
    }
    T &operator*() const { return *it; }
    T *operator->() const noexcept { return it.operator->(); }
    bool operator==(const iterator &rhs) const { return it == rhs.it; }
    bool operator!=(const iterator &rhs) const { return it != rhs.it; }
    bool operator==(const const_iterator &rhs) const { return it == rhs.it; }
    bool operator!=(const const_iterator &rhs) const { return it != rhs.it; }
  };

  class const_iterator {
    friend class deque;
    friend class iterator;
    const deque *owner{};
    typename base_t::const_iterator it;
    const_iterator(const deque *o, typename base_t::const_iterator i)
        : owner(o), it(i) {}

  public:
    const_iterator() = default;
    const_iterator(const iterator &other) : owner(other.owner), it(other.it) {}
    const_iterator operator+(const int &n) const {
      return const_iterator(owner, it + n);
    }
    const_iterator operator-(const int &n) const {
      return const_iterator(owner, it - n);
    }
    int operator-(const const_iterator &rhs) const {
      if (owner != rhs.owner) throw invalid_iterator();
      return static_cast<int>(it - rhs.it);
    }
    const_iterator &operator+=(const int &n) {
      it += n;
      return *this;
    }
    const_iterator &operator-=(const int &n) {
      it -= n;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator tmp = *this;
      ++it;
      return tmp;
    }
    const_iterator &operator++() {
      ++it;
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator tmp = *this;
      --it;
      return tmp;
    }
    const_iterator &operator--() {
      --it;
      return *this;
    }
    const T &operator*() const { return *it; }
    const T *operator->() const noexcept { return it.operator->(); }
    bool operator==(const iterator &rhs) const { return it == rhs.it; }
    bool operator==(const const_iterator &rhs) const { return it == rhs.it; }
    bool operator!=(const iterator &rhs) const { return it != rhs.it; }
    bool operator!=(const const_iterator &rhs) const { return it != rhs.it; }
  };

  // constructors, assignment, destructor
  deque() = default;
  deque(const deque &other) : d(other.d) {}
  ~deque() = default;
  deque &operator=(const deque &other) {
    if (this != &other) d = other.d;
    return *this;
  }

  // element access
  T &at(const size_t &pos) {
    if (pos >= d.size()) throw index_out_of_bound();
    return d.at(pos);
  }
  const T &at(const size_t &pos) const {
    if (pos >= d.size()) throw index_out_of_bound();
    return d.at(pos);
  }
  T &operator[](const size_t &pos) {
    if (pos >= d.size()) throw index_out_of_bound();
    return d[pos];
  }
  const T &operator[](const size_t &pos) const {
    if (pos >= d.size()) throw index_out_of_bound();
    return d[pos];
  }
  const T &front() const {
    if (d.empty()) throw container_is_empty();
    return d.front();
  }
  const T &back() const {
    if (d.empty()) throw container_is_empty();
    return d.back();
  }

  // iterators
  iterator begin() { return iterator(this, d.begin()); }
  const_iterator cbegin() const { return const_iterator(this, d.cbegin()); }
  iterator end() { return iterator(this, d.end()); }
  const_iterator cend() const { return const_iterator(this, d.cend()); }

  // capacity
  bool empty() const { return d.empty(); }
  size_t size() const { return d.size(); }

  // modifiers
  void clear() { d.clear(); }
  iterator insert(iterator pos, const T &value) {
    if (pos.owner != this) throw invalid_iterator();
    auto it2 = d.insert(pos.it, value);
    return iterator(this, it2);
  }
  iterator erase(iterator pos) {
    if (d.empty()) throw container_is_empty();
    if (pos.owner != this) throw invalid_iterator();
    auto it2 = d.erase(pos.it);
    return iterator(this, it2);
  }
  void push_back(const T &value) { d.push_back(value); }
  void pop_back() {
    if (d.empty()) throw container_is_empty();
    d.pop_back();
  }
  void push_front(const T &value) { d.push_front(value); }
  void pop_front() {
    if (d.empty()) throw container_is_empty();
    d.pop_front();
  }
};

} // namespace sjtu

#endif
