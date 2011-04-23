#ifndef _PERCEPTRON_HPP
#define _PERCEPTRON_HPP

#include "document.hpp"
#include "featurevector.hpp"

template <typename Featuriser>
class Perceptron {
private:
  Featuriser f;
  FeatureVector current;
  FeatureVector avg;
  std::map<size_t, double> last_update;
  size_t time;

  short get_sign(double value) const {
    if (value < 0)
      return -1;
    else
      return 1;
  }

public:
  Perceptron() : time(0) {}

  short classify(Document& instance, bool train=false) {
    if (!(instance.has_features()))
      f.set_feature_vector(instance);
    if (!train)
      return get_sign(dot_product(avg, instance.get_features()));
    else
      return get_sign(dot_product(current, instance.get_features()));
  }

  void train(Document& instance, short label) {
    ++time;
    if (!(instance.has_features()))
      f.set_feature_vector(instance);
    short prediction = classify(instance, true);
    if (prediction != label) {
      FeatureVector fv = instance.get_features();
      for (FeatureVector::iterator it = fv.begin(); it != fv.end(); ++it) {
	int key = it->first;
	double value = current[key];
	double last_update_value = last_update[key];
	avg[key] += (time - last_update_value) * value;
	last_update[key] = time;
      }
      current.sum_update(instance.get_features(), label);
    }
  }

  void finalise() {
    for (FeatureVector::iterator it = current.begin(); it != current.end(); ++it) {
      int key = it->first;
      double value = it->second;;
      double last_update_value = last_update[key];
      avg[key] += (time - last_update_value) * value;
    }
  }
};

#endif
