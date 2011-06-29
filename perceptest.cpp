#include "perceptron.hpp"
#include "tf.hpp"
#include "tokeniser.hpp"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

#define PR(x) \
  std::cout << #x << " = " << x << std::endl;

typedef std::pair<Document, short> DocPair;

FeaturePair split_feat_token(const std::string& token) {
  size_t index = token.find(':');
  std::string feat_id(token.begin(), token.begin() + index);
  std::string feat_value(token.begin() + index + 1, token.end());
  return FeaturePair(std::atoi(feat_id.c_str()),
		     std::atof(feat_value.c_str()));
}

void read_data(const char* file, std::vector<DocPair>& v) {
  std::ifstream in(file);
  std::string token;
  short doc_class = 0;
  FeatureVector fv;
  Document doc;
  while (in >> token) {
    if ((token == "-1") || (token == "+1")) {
      if (doc_class != 0) {
	doc.set_features(fv);
	v.push_back(std::make_pair(doc, doc_class));
	fv.clear();
      }
      doc_class = std::atoi(token.c_str());
    }
    else
      fv.push_back(split_feat_token(token));
  }
  // push back last vector
  v.push_back(std::make_pair(doc, doc_class));
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
  // some 'dumb' scoring; can also calculate more nuanced F-scores
  std::cerr << "correct = " << correct << '\n';
  std::cerr << "wrong = " << wrong << '\n';
  std::cerr << "accuracy = " << double(correct) / v.size() << '\n';
}

int main(int argc, char* argv[]) {
  Perceptron<TF<StdTokeniser> > p;
  std::vector<DocPair> training_set, testing_set;
  std::cout << "reading data..." << '\n';
  read_data(argv[1], training_set);
  read_data(argv[2], testing_set);
  std::cout << "training..." << '\n';
  std::srand(11);
  size_t num_iterations = 1;
  if (argc > 3)
    num_iterations = std::atoi(argv[3]);
  for (size_t i = 0; i < num_iterations; i++) {
    std::random_shuffle(training_set.begin(), training_set.end());
    train(training_set, p);
    p.finalise();
  }
  std::cout << "classifying..." << std::endl;
  classify(testing_set, p);
}
