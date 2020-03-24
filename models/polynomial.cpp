#include "polynomial.h"

#include <iostream>

namespace models {
namespace {

using namespace std;

} // namespace

bool Polynomial::IsNull() const {
  // TODO: map
  return coefficients_.empty() || 
    (coefficients_.size() == 1 && coefficients_[1] == 0);
}

unsigned long long Polynomial::GetDegree() const {
  // return coefficients_.empty() ? 0 : coefficients_.rbegin()->first;
  return coefficients_.empty() ? 0 : coefficients_.size() - 1;
}

long long Polynomial::GetCoefficientForExponent(
  const unsigned long long exponent) const {
  // return coefficients_.find(exponent) == coefficients_.end() ? 0 : 
  //   coefficients_.at(exponent);
  if (exponent >= coefficients_.size()) {
    return 0;
  }
  return coefficients_[exponent];
}

void Polynomial::AddCoefficientToExponent(
  const unsigned long long exponent, 
  const long long coefficient) {
  // coefficients_.find(exponent) == coefficients_.end() ?
  //   coefficients_[exponent] = coefficient :
  //   coefficients_.at(exponent) += coefficient;
  // // Remove if 0.
  // if (!coefficients_.at(exponent)) {
  //   coefficients_.erase(exponent);
  // }

  if (exponent >= coefficients_.size()) {
    coefficients_.resize(exponent + 1);
  }
  coefficients_[exponent] += coefficient;
  // Remove if 0.
  if (exponent == coefficients_.size() - 1 && !coefficients_[exponent]) {
    coefficients_.resize(exponent);
  }
}

const void* Polynomial::GetCoefficientsPointer() const {
  return &coefficients_[0];
}

} // namespace models
