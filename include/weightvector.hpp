#ifndef _WEIGHTVECTOR_HPP
#define _WEIGHTVECTOR_HPP

#include "featurevector.hpp"
#include <vector>


class WeightVector {
private:
  std::vector<double> weights;
public:
  WeightVector();
  double dot_product(const FeatureVector&);
  void sum_update(const FeatureVector&, int);
  double& operator[](size_t);
  const double& operator[](size_t) const;
  size_t size() const;
};

#endif
