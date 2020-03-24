#ifndef OPERATIONS_PARALLEL_OPERATIONS_H
#define OPERATIONS_PARALLEL_OPERATIONS_H

#include <string>
#include <vector>

#include "../models/polynomial.h"

namespace operations {

// Computes the multiplication of the two given polynomials and returns the 
// result. This method is part of a parallel implementation and will be called
// only by one process (the main process aka process 0).
models::Polynomial ComputeMultiplicationParent(
  const models::Polynomial& first_polynomial, 
  const models::Polynomial& second_polynomial,
  const unsigned int number_of_processes);

// This method is part of a parallel implementation and will be called by all
// the processes but one (the main process aka process 0).
void ComputeMultiplicationChild(const int process_index);

} // namespace operations 

#endif // OPERATIONS_SEQUENTIAL_OPERATIONS_H
