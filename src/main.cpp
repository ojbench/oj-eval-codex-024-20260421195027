#include <bits/stdc++.h>
#include "sjtu/deque.hpp"
#include "sjtu/exceptions.hpp"

// We will compile into an empty main that does nothing.
// OJ will run its own tests; only binary name matters.
int main() {
  // Self-check: basic operations (optional, no output)
  sjtu::deque<int> d;
  d.push_back(1);
  d.push_front(2);
  d.pop_back();
  if (!d.empty()) (void)d.front();
  return 0;
}

