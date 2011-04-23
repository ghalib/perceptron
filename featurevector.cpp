#include <iostream>
#include <cmath>
#include "featurevector.hpp"

FeatureVector::FeatureVector() {}

double FeatureVector::get_norm() {
  double norm = 0.0;
  for (iterator it = begin(); it != end(); ++it)
    norm += it->second * it->second;
  norm = std::sqrt(norm);
  return norm;
}

void FeatureVector::sum_update(const FeatureVector& other,
			       short sign) {
  FeatureVector::const_iterator it;
  for (it = other.begin(); it != other.end(); ++it) {
    int id = it->first;
    double value = it->second;
    (*this)[id] += (sign * value);
  }
}

double dot_product(const FeatureVector& fv1, const FeatureVector& fv2) {
  double result = 0.0;
  FeatureVector::const_iterator it2;
  for (it2 = fv2.begin(); it2 != fv2.end(); ++it2) {
    int feat_id = it2->first;
    FeatureVector::const_iterator it1 = fv1.find(feat_id);
    if (it1 != fv1.end())
      result += (it1->second * it2->second);
  }
  return result;
}
