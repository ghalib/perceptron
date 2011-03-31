#include "vocabulary.hpp"

bool Vocabulary::contains(const std::string& token) {
  return (vocab.find(token) != vocab.end());
}

int Vocabulary::put(const std::string& token) {
  if (!contains(token)) {
    vocab[token] = id;
    id++;
  }
  return vocab[token];
}

int Vocabulary::get(const std::string& token) {
  if (contains(token))
    return vocab[token];
  else
    return oov;
}
  
size_t Vocabulary::size() {
  return id;
}
