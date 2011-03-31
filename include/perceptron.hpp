#ifndef _PERCEPTRON_HPP
#define _PERCEPTRON_HPP

#include "document.hpp"
#include "featurevector.hpp"

template <typename Featuriser>
class Perceptron {
private:
  FeatureVector weightvector;
  Featuriser f;
  short get_sign(double value) const {
    if (value < 0)
      return -1;
    else
      return 1;
  }
public:
  FeatureVector get_weightvector() const {
    return weightvector;
  }
  short classify(Document& instance) const {
    if (!(instance.has_features()))
      f.set_feature_vector(instance);
    return get_sign(dot_product(weightvector, instance.get_features()));
  }
  void train(Document& instance, short label) {
    if (!(instance.has_features()))
      f.set_feature_vector(instance);
    short prediction = classify(instance);
    if (prediction != label) {
      weightvector.sum_update(instance.get_features(), prediction);
    }
  }
};

#endif
