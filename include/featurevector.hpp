#ifndef _FEATUREVECTOR_HPP
#define _FEATUREVECTOR_HPP

#include <map>

class FeatureVector : public std::map<int, double> {
public:
  FeatureVector();
  bool contains(int) const;
  double get_norm();
  void sum_update(const FeatureVector&, short);
};

double dot_product(const FeatureVector&, const FeatureVector&);

#endif
