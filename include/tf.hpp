#ifndef _TF_HPP
#define _TF_HPP

// This class converts our documents into features.  For features we
// simply use weighted unigram term frequencies, where each term
// frequency is divided by the number of total terms in that document.

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include "vocabulary.hpp"
#include "featurevector.hpp"
#include "tokeniser.hpp"
#include "document.hpp"

template<typename Tokeniser>
class TF {
private:
  Tokeniser tokeniser;
  Vocabulary vocab;
  typedef std::pair<std::map<std::string, size_t>, size_t> TFPair;
  TFPair compute_term_freq(const std::string& s) {
    std::map<std::string, size_t> tf;
    std::vector<std::string> tokens;
    tokeniser.tokenise(s, tokens);
    size_t total = 0;
    for (size_t i = 0; i < tokens.size(); i++) {
      vocab.put(tokens[i]);
      tf[tokens[i]]++;
      total++;
    }
    return TFPair(tf, total);
  }
public:
  void set_feature_vector(Document& doc) {
    TFPair tfpair = compute_term_freq(doc.get_content());
    size_t total = tfpair.second;
    FeatureVector fv;
    TFPair::first_type::iterator it;
    for (it = tfpair.first.begin(); it != tfpair.first.end(); ++it) {
      int feat_id = vocab.put(it->first);
      double feat_value = double(it->second) / total;
      fv[feat_id] = feat_value;
    }
    doc.set_features(fv);
  }
};

#endif
