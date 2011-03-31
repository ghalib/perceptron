#ifndef _VOCABULARY_HPP
#define _VOCABULARY_HPP

// Convert strings to ints for feature ids.

#include <string>
#include <map>

class Vocabulary {
private:
  std::map<std::string, int> vocab;
  int id;
  const int oov;
  bool contains(const std::string&);
public:
  Vocabulary() : id(0), oov(-1) {}

  template<typename Iter>
  Vocabulary(Iter begin, Iter end) : id(0), oov(-1) {
    for (Iter it = begin; it != end; ++it)
      put(*it);
  }
  int put(const std::string&);
  int get(const std::string&);
  size_t size();
};

#endif
