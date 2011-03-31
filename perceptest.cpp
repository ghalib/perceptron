#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "perceptron.hpp"
#include "tf.hpp"
#include "tokeniser.hpp"
#include <iostream>

int main() {
  Perceptron<TF<StdTokeniser> > p;
}
