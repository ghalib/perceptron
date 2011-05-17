#ifndef _FEATUREVECTOR_HPP
#define _FEATUREVECTOR_HPP

#include <vector>

struct FeaturePair {
  size_t id;
  double value;
  FeaturePair() : id(0), value(0) {}
  FeaturePair(size_t id_, double val) : id(id_), value(val) {}
};

typedef std::vector<FeaturePair> FeatureVector;

#endif
