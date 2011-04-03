#include "perceptron.hpp"
#include "tf.hpp"
#include "tokeniser.hpp"
#include <fstream>
#include <iostream>

std::string get_file_content(const std::string& filename) {
  std::ifstream in(filename.c_str());
  std::string line;
  std::string content;
  while (std::getline(in, line)) {
    line.push_back('\n');
    content += line;
  }
  return content;
}

int main(int argc, char* argv[]) {
  Perceptron<TF<StdTokeniser> > p;
}
