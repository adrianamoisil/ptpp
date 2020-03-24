#ifndef UTILS_UTILS_H
#define UTILS_UTILS_H

#include <string>

#include "../models/polynomial.h"

namespace utils {

// Generate a polynomial and saves it to the given file. The file contains 
// maximum_exponent + 1 lines, each line containing a pair 
// (coefficient, exponent), in order from the smallest coefficient (0) to the 
// biggest.
void GeneratePolynomial(
  const std::string& filename, 
  const unsigned long long maximum_exponent,
  const short maximum_coefficient, 
  const bool allow_zero_as_coefficient);

// Checks whether the two given polynomials are identical.
bool ComparePolynomials(
  const models::Polynomial& first_polynomial,
  const models::Polynomial& second_polynomial);

// Checks whether the two given files contain the same polynomials.
bool ComparePolynomials(
  const std::string& first_filename,
  const std::string& second_filename);

} // namespace utils 

#endif // UTILS_UTILS_H
