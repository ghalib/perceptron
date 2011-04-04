#ifndef _PERCEPTRON_HPP
#define _PERCEPTRON_HPP

#include "document.hpp"
#include "featurevector.hpp"
#include <iostream>

template <typename Featuriser>
class Perceptron {
private:
  Featuriser f;
  FeatureVector weightvector;
  FeatureVector avg;

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

  short classify(Document& instance) {
    if (!(instance.has_features()))
      f.set_feature_vector(instance);
    return get_sign(dot_product(avg, instance.get_features()));
  }

  void train(Document& instance, short label) {
    if (!(instance.has_features()))
      f.set_feature_vector(instance);
    short prediction = classify(instance);
    if (prediction != label) {
      weightvector.sum_update(instance.get_features(), label);
    }
    avg.sum_update(weightvector, 1);
  }
};

#endif
