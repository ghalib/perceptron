#include "perceptron.hpp"
#include "tf.hpp"
#include "tokeniser.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <utility>

typedef std::pair<Document, short> DocPair;

std::pair<size_t, double> split_feat_token(const std::string& token) {
  size_t index = token.find(':');
  std::string feat_id(token.begin(), token.begin() + index);
  std::string feat_value(token.begin() + index + 1, token.end());
  return std::make_pair(std::atoi(feat_id.c_str()),
			std::atof(feat_value.c_str()));
}

void read_data(const char* file, std::vector<DocPair>& v) {
  std::ifstream in(file);
  std::string token;
  short doc_class = 0;
  FeatureVector fv;
  while (in >> token) {
    if ((token == "-1") || (token == "+1")) {
      if (doc_class != 0) {
	Document doc;
	doc.set_features(fv);
	v.push_back(std::make_pair(doc, doc_class));
	fv.clear();
      }
      doc_class = std::atoi(token.c_str());
    }
    else {
      std::pair<size_t, double> feature = split_feat_token(token);
      size_t feat_id = feature.first;
      double feat_value = feature.second;
      fv[feat_id] = feat_value;
    }
  }
}

template<typename Featuriser>
void train(std::vector<DocPair>& v, Perceptron<Featuriser>& p) {
  for (size_t i = 0; i < v.size(); i++)
    p.train(v[i].first, v[i].second);
}
  
template<typename Featuriser>
void classify(std::vector<DocPair>& v, Perceptron<Featuriser>& p) {
  size_t correct = 0;
  size_t wrong = 0;
  for (size_t i = 0; i < v.size(); i++) {
    int doc_class = v[i].second;
    if (doc_class == p.classify(v[i].first))
      correct += 1;
    else
      wrong += 1;
  }
  std::cout << "correct = " << correct << '\n';
  std::cout << "wrong = " << wrong << '\n';
}

int main(int argc, char* argv[]) {
  Perceptron<TF<StdTokeniser> > p;
  std::vector<DocPair> training_set, testing_set;
  std::cout << "reading data..." << '\n';
  read_data("/Users/ghalib/datasets/news20.binary/train", training_set);
  read_data("/Users/ghalib/datasets/news20.binary/test", testing_set);
  std::cout << "training..." << '\n';
  std::srand(11);
  for (int i = 0; i < 1; i++) {
    std::random_shuffle(training_set.begin(), training_set.end());
    train(training_set, p);
  }
  std::cout << "classifying..." << std::endl;
  classify(testing_set, p);
}
