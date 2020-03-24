#include "utils.h"

#include <fstream>
#include <iostream>

#include "read_utils.h"

namespace utils {
namespace {

using namespace models;
using namespace std;

} // namespace

void GeneratePolynomial(const string& filename, 
  const unsigned long long maximum_exponent,
  const short maximum_coefficient, 
  const bool allow_zero_as_coefficient) {
  ofstream output_stream(filename);
  if (!output_stream.is_open()) {
    cerr << "Failed to open " << filename << ".\n";
    exit(-1);
  }

  for (unsigned long long exponent = 0; exponent <= maximum_exponent; ++exponent) {
    // The first coefficient will never be 0 if allow_zero_as_coefficient is
    // true.
    const short coefficient = 
      (exponent == maximum_exponent || !allow_zero_as_coefficient) ? 
      1 + rand() % (maximum_coefficient) :
      rand() % (maximum_coefficient + 1); 
    output_stream << coefficient << " " << exponent << "\n";
  }
  
  output_stream.close();
}

bool ComparePolynomials(
  const Polynomial& first_polynomial,
  const Polynomial& second_polynomial) {
  const unsigned long long first_polynomial_degree = 
    first_polynomial.GetDegree();
  const unsigned long long second_polynomial_degree = 
    first_polynomial.GetDegree();
  if (first_polynomial_degree != second_polynomial_degree) {
    return false;
  }

  for (unsigned long long exponent = 0; exponent <= first_polynomial_degree; ++exponent) {
    const long long first_coefficient = 
      first_polynomial.GetCoefficientForExponent(exponent);
    const long long second_coefficient = 
      second_polynomial.GetCoefficientForExponent(exponent);
    if (first_coefficient != second_coefficient) {
      return false;
    }
  }

  return true;
}

bool ComparePolynomials(
  const string& first_filename,
  const string& second_filename) {
  const Polynomial first_polynomial = ReadFromFile(first_filename);
  const Polynomial second_polynomial = ReadFromFile(second_filename);
  return ComparePolynomials(first_polynomial, second_polynomial);
}

} // namespace utils 