#ifndef MODELS_POLYNOMIAL_H
#define MODELS_POLYNOMIAL_H

#include <map>
#include <vector>

namespace models {

class Polynomial {
public:
  // Polynomial(const std::map<unsigned long long, long long>& coefficients = {}) :
  //   coefficients_(coefficients) {}
  Polynomial(const std::vector<long long>& coefficients = {}) :
    coefficients_(coefficients) {}

	// Returns true if the Polynomial's degree is 0 and the coefficient for the 
  // exponent 0 is also 0.
  bool IsNull() const;

  // Returns the Polynomial's degree.
  unsigned long long GetDegree() const;

  // Returns the coefficient for the given exponent.
  long long GetCoefficientForExponent(const unsigned long long exponent) const;

  // Increases the coefficient for the given exponent with the given value.
  void AddCoefficientToExponent(const unsigned long long exponent, 
    const long long coefficient);

  const void* GetCoefficientsPointer() const;

private:
  // std::map<unsigned long long, long long> coefficients_;
  std::vector<long long> coefficients_;
};

} // namespace models

#endif // MODELS_POLYNOMIAL_H