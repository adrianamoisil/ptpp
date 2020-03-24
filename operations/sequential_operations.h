#ifndef OPERATIONS_SEQUENTIAL_OPERATIONS_H
#define OPERATIONS_SEQUENTIAL_OPERATIONS_H

#include <string>
#include <vector>

#include "../models/polynomial.h"

namespace operations {

// Computes the multiplication of the two given polynomials and returns the 
// result. This method uses a sequential implementation. 
models::Polynomial ComputeMultiplication(
  const models::Polynomial& first_polynomial, 
  const models::Polynomial& second_polynomial);

} // namespace operations 

#endif // OPERATIONS_SEQUENTIAL_OPERATIONS_H
