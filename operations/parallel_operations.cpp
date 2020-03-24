#include "parallel_operations.h"

#include <iostream>
#include <unordered_map>
#include <map>
#include <mpi.h>

#include "../consts/mpi_tags.h"
#include "../utils/mpi_utils.h"

namespace operations {
namespace {

using namespace consts;
using namespace models;
using namespace std;
using namespace utils;

Polynomial ComputePartialResult(
  const Polynomial& first_polynomial, 
  const Polynomial& second_polynomial,
  const unsigned long long start_position,
  const unsigned long long number_of_operations) {
  const unsigned long long first_polynomial_degree = 
    first_polynomial.GetDegree();
  const unsigned long long second_polynomial_degree = 
    second_polynomial.GetDegree();
  
  unsigned long long count = 0;
  Polynomial partial_result;
  const unsigned long long first_exponent_initial_value = 
    start_position / (second_polynomial_degree + 1);
  const unsigned long long second_exponent_initial_value = 
    start_position % (second_polynomial_degree + 1);

  for (unsigned long long first_exponent = first_exponent_initial_value; first_exponent <= first_polynomial_degree; ++first_exponent) {
    for (unsigned long long second_exponent = 0; second_exponent <= second_polynomial_degree; ++second_exponent) {
      if (first_exponent == first_exponent_initial_value && !second_exponent) {
        second_exponent = second_exponent_initial_value;
      }

      const unsigned long long exponent = first_exponent + second_exponent;
      const long long coefficient = 
        first_polynomial.GetCoefficientForExponent(first_exponent) *
        second_polynomial.GetCoefficientForExponent(second_exponent);
      partial_result.AddCoefficientToExponent(exponent, coefficient);
      ++count;
      if (count == number_of_operations) {
        return partial_result;
      }
    }
  }

  // No process should reach this point. Terminate the program.
  cerr << "ComputePartialResult: this line should not have been reached.\n";
  cerr << "start_position = " << start_position << "\n";
  cerr << "number_of_operations = " << number_of_operations << "\n";
  cerr << "first_exponent_initial_value = " << first_exponent_initial_value << "\n";
  cerr << "second_exponent_initial_value = " << second_exponent_initial_value << "\n";
  cerr << "count = " << count << "\n";
  exit(-1);
}

void AddPolynomial(
  const Polynomial& polynomial,
  Polynomial* result) {
  const auto polynomial_degree = polynomial.GetDegree();
  for (unsigned long long exponent = 0; exponent <= polynomial_degree; ++exponent) {
    const auto coefficient = polynomial.GetCoefficientForExponent(exponent);
    result->AddCoefficientToExponent(exponent, coefficient);
  }
}

} // namespace

Polynomial ComputeMultiplicationParent(
  const Polynomial& first_polynomial, 
  const Polynomial& second_polynomial,
  const unsigned int number_of_processes) {
  // Total number of operations required to be done. One operation represents
  // the multiplications of two coefficients. This means that, in order to 
  // compute the multiplication result of two polyinomials, there will be 
  // required a total of (n + 1) x (m + 1) operations, where n, m are the 
  // degrees of the two polynomials.
  const unsigned long long first_polynomial_degree = 
    first_polynomial.GetDegree();
  const unsigned long long second_polynomial_degree = 
    second_polynomial.GetDegree();
  const unsigned long long total_number_of_operations = 
    (first_polynomial_degree + 1) * (second_polynomial_degree + 1);

  // The minimum number of operations a process will have to do (including the 
  // parent process). total_number_of_operations might not be divisible with
  // number_of_processes, so the rest R will be divided equally to the first
  // R processes (each of these processes will have one more operation to do).
  const unsigned long long minimum_number_of_operations_per_process =
    total_number_of_operations / number_of_processes;
  unsigned long long remaining_operations = 
    total_number_of_operations % number_of_processes;
  unsigned long long start_position = 0;
  
  // This process (the parent process) is the one with index 0.
  for (unsigned int process_index = 1; process_index < number_of_processes; ++process_index) {
    // Send the two polynomials.
    MpiSendPolynomial(first_polynomial, process_index, kFirstPolynomialSizeMpiTag, kFirstPolynomialMpiTag);
    MpiSendPolynomial(second_polynomial, process_index, kSecondPolynomialSizeMpiTag, kSecondPolynomialMpiTag);
    
    // Compute the number of operations the process process_index is responsible 
    // for.
    unsigned long long number_of_operations = 
      minimum_number_of_operations_per_process;
    if (remaining_operations) {
      --remaining_operations;
      ++number_of_operations;
    } 
  
    MPI_Send(&start_position, 1, MPI_UNSIGNED_LONG_LONG, process_index, 
      kStartPositionMpiTag, MPI_COMM_WORLD);
    // Send the number of operations that this thread will be responsible for.
    MPI_Send(&number_of_operations, 1, MPI_UNSIGNED_LONG_LONG, process_index, 
      kNumberOfOperationsMpiTag, MPI_COMM_WORLD);
    
    start_position += number_of_operations;
  }

  // The current process (aka the parent process, the one with index 0) will be
  // repsonsible for the last group of operations. We know for sure that, at 
  // this point, remaining_operations is 0, so the number of operations the 
  // parent porcess has to do is minimum_number_of_operations_per_process.
  Polynomial result = ComputePartialResult(first_polynomial, second_polynomial, 
    start_position, minimum_number_of_operations_per_process);

  for (unsigned int process_index = 1; process_index < number_of_processes; ++process_index) {
    const Polynomial partial_result = 
      MpiRecvPolynomial(process_index, kPartialResultSizeMpiTag, kPartialResultMpiTag);
    AddPolynomial(partial_result, &result);
  }

  return result;
}

void ComputeMultiplicationChild(const int process_index) {
  // Receive the two polynomials.
  const Polynomial first_polynomial = 
    MpiRecvPolynomial(0, kFirstPolynomialSizeMpiTag, kFirstPolynomialMpiTag);
  const Polynomial second_polynomial = 
    MpiRecvPolynomial(0, kSecondPolynomialSizeMpiTag, kSecondPolynomialMpiTag);

  unsigned long long start_position;
  unsigned long long number_of_operations;
  MPI_Recv(&start_position, 1, MPI_UNSIGNED_LONG_LONG, 0,
    kStartPositionMpiTag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  // Receive the number of operations that this thread will be responsible for.
  MPI_Recv(&number_of_operations, 1, MPI_UNSIGNED_LONG_LONG, 0,
    kNumberOfOperationsMpiTag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  const Polynomial partial_result = ComputePartialResult(first_polynomial, 
    second_polynomial, start_position, number_of_operations);
  
  MpiSendPolynomial(partial_result, 0, kPartialResultSizeMpiTag, kPartialResultMpiTag);
}

} // namespace operations
