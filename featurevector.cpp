#include <iostream>
#include <cmath>
#include "featurevector.hpp"

FeatureVector::FeatureVector() {}

bool FeatureVector::contains(int id) const {
  return (find(id) != end());
}

double FeatureVector::get_norm() {
  double norm = 0.0;
  for (iterator it = begin(); it != end(); ++it)
    norm += it->second * it->second;
  norm = std::sqrt(norm);
  return norm;
}

void FeatureVector::sum_update(const FeatureVector& other,
			       short sign=1) {
  // in-place sum
  FeatureVector result;
  // FeatureVectors are std::maps which means they are ordered
  iterator it1 = begin();
  FeatureVector::const_iterator it2 = other.begin();
  while ((it1 != end()) && (it2 != other.end())) {
    int id1 = it1->first;
    double feat_value1 = it1->second;
    int id2 = it2->first;
    double feat_value2 = it2->second;
    if (id1 < id2) {
      (*this)[id1] += (sign * feat_value1);
      ++it1;
    }
    else if (id1 > id2) {
      (*this)[id2] += (sign * feat_value2);
      ++it2;
    }
    else {
      ++it1;
      ++it2;
    }
    if (it1 == end()) {
      while (it2 != other.end()) {
	(*this)[it2->first] += (sign * it2->second);
      }
    }
    else if (it2 == other.end()) {
      while (it1 != end()) {
	(*this)[it1->first] += (sign * it1->second);
      }
    }
  }
}

double dot_product(const FeatureVector& fv1, const FeatureVector& fv2) {
  double result = 0.0;
  FeatureVector::const_iterator it1;
  for (it1 = fv1.begin(); it1 != fv1.end(); ++it1) {
    int feat_id = it1->first;
    FeatureVector::const_iterator it2 = fv2.find(feat_id);
    if (it2 != fv2.end())
      result += (it1->second * it2->second);
  }
  return result;
}
