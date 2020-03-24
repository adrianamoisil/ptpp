#include "write_utils.h"

#include <fstream>
#include <iostream>

namespace utils {
namespace {

using namespace models;
using namespace std;

} // namespace

void WriteToFile(
  const Polynomial& polynomial,
  const string& filename) {
  ofstream output_stream(filename);
  if (!output_stream.is_open()) {
    cerr << "Failed to open " << filename << ".\n";
    exit(-1);
  }

  const long long polynomial_degree = polynomial.GetDegree();
  for (long long exponent = 0; exponent <= polynomial_degree; ++exponent) {
    output_stream << polynomial.GetCoefficientForExponent(exponent) << " "
      << exponent << "\n";
  }
  output_stream.close();
}

void WriteToStdout(const Polynomial& polynomial) {
  const long long polynomial_degree = polynomial.GetDegree();
  for (long long exponent = 0; exponent <= polynomial_degree; ++exponent) {
    cout << polynomial.GetCoefficientForExponent(exponent) << " "
      << exponent << "\n";
  }
}

void WriteLineToCsvFile(
  const string& filename, 
  const vector<long long>& values) {
  ofstream output_stream(filename,
  ofstream::out | ofstream::app);
  for (size_t index = 0; index < values.size(); ++index) {
    output_stream <<  values[index];
    if (index != values.size() - 1) {
      output_stream << ",";
    }  
  }
  output_stream << "\n";
  output_stream.close();

}

} // namespace utils 