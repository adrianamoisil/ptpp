#include "sequential_operations.h"

#include <iostream>
#include <vector>

#include "../utils/write_utils.h"

namespace operations {
namespace {

using namespace models;
using namespace std;
using namespace utils;

} // namespace

Polynomial ComputeMultiplication(
  const Polynomial& first_polynomial, 
  const Polynomial& second_polynomial) {
  // Return a null polynomial if any of the given two polynomials is null,
  if (first_polynomial.IsNull() || second_polynomial.IsNull()) {
    return Polynomial();
  }

  const unsigned long long first_polynomial_degree = 
    first_polynomial.GetDegree();
  const unsigned long long second_polynomial_degree = 
    second_polynomial.GetDegree();

  Polynomial result;
  
  for (unsigned long long first_exponent = 0; first_exponent <= first_polynomial_degree; ++first_exponent) {
    for (unsigned long long second_exponent = 0; second_exponent <= second_polynomial_degree; ++second_exponent) {
      const unsigned long long exponent = first_exponent + second_exponent;
      const long long coefficient = 
        first_polynomial.GetCoefficientForExponent(first_exponent) *
        second_polynomial.GetCoefficientForExponent(second_exponent);
      result.AddCoefficientToExponent(exponent, coefficient);
    }
  }

  return result;
}

} // namespace operations
