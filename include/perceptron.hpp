#ifndef _PERCEPTRON_HPP
#define _PERCEPTRON_HPP

#include "document.hpp"
#include "featurevector.hpp"
#include "weightvector.hpp"
#include <iostream>
#include <map>

template <typename Featuriser>
class Perceptron {
private:
  Featuriser f;
  WeightVector current;
  WeightVector avg;
  std::map<size_t, double> last_update;
  size_t current_time;

  short get_sign(double value) const {
    if (value < 0)
      return -1;
    else
      return 1;
  }

public:
  Perceptron() : current_time(0) {}

  short classify(Document& instance, bool train=false) {
    if (!(instance.has_features()))
      f.set_feature_vector(instance);
    if (!train)
      return get_sign(avg.dot_product(instance.get_features()));
    else
      return get_sign(current.dot_product(instance.get_features()));
  }

  void train(Document& instance, short label) {
    ++current_time;
    if (!(instance.has_features()))
      f.set_feature_vector(instance);
    short prediction = classify(instance, true);
    if (prediction != label) {
      FeatureVector fv = instance.get_features();
      for (FeatureVector::iterator it = fv.begin(); it != fv.end(); ++it) {
	int key = it->id;
	double value = current[key];
	double last_update_time = last_update[key];
	avg[key] += (current_time - last_update_time) * value;
	last_update[key] = current_time;
      }
      current.sum_update(instance.get_features(), label);
    }
  }

  void finalise() {
    for (size_t id = 0; id < current.size(); id++) {
      double value = current[id];
      double last_update_time = last_update[id];
      avg[id] += (current_time - last_update_time) * value;
    }
  }
};

#endif
