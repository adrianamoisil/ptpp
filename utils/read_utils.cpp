#include "read_utils.h"

#include <fstream>
#include <iostream>
#include <vector>

namespace utils {
namespace {

using namespace models;
using namespace std;

} // namespace

Polynomial ReadFromFile(const string& filename) {
  ifstream input_stream(filename);
  if (!input_stream.is_open()) {
    cerr << "Failed to open " << filename << ".\n";
    exit(-1);
  }

  Polynomial polynomial;
  long long coefficient;
  unsigned long long exponent;
  while (input_stream >> coefficient) {
    input_stream >> exponent;
    polynomial.AddCoefficientToExponent(exponent, coefficient);
  }
  input_stream.close();
  return {polynomial};
}

} // namespace utils 