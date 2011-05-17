#include "weightvector.hpp"
#include <iostream>

#define PR(x) \
  std::cerr << #x << " = " << x << std::endl;

WeightVector::WeightVector() {}

double WeightVector::dot_product(const FeatureVector& fv) {
  double result = 0;
  FeatureVector::const_iterator it;
  for (it = fv.begin(); it != fv.end(); ++it) {
    result += (*this)[it->id] * it->value;
  }
  return result;
}

void WeightVector::sum_update(const FeatureVector& fv, int sign) {
  FeatureVector::const_iterator it;
  for (it = fv.begin(); it != fv.end(); ++it)
    (*this)[it->id] += (sign * it->value);
}

double& WeightVector::operator[](size_t index) {
  if (index >= size()) 
    weights.resize(index + 10);
  return weights[index];
}

const double& WeightVector::operator[](size_t index) const {
  return (*this)[index];
}

size_t WeightVector::size() const {
  return weights.size();
}

