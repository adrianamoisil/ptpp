#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <mpi.h>

#include "models/polynomial.h"
#include "operations/sequential_operations.h"
#include "operations/parallel_operations.h"
#include "utils/read_utils.h"
#include "utils/utils.h"
#include "utils/write_utils.h"

namespace {

using namespace models;
using namespace operations;
using namespace std;
using namespace utils;

// The file containing the first polynomial.
static const string first_polynomial_file =
  "/home/adriana/Documents/uni/ppd2/src/data/first_polynomial.txt"; 
// The file containing the second polynomial.
static const string second_polynomial_file =
  "/home/adriana/Documents/uni/ppd2/src/data/second_polynomial.txt";
// The file where to write the result.
static const string result_file =
  "/home/adriana/Documents/uni/ppd2/src/results/parallel_result.txt";
// The file where to write the correct result used to check whether our approach
// worked.
static const string validator_result_file =
  "/home/adriana/Documents/uni/ppd2/src/results/validator_result.txt";
// The csv file where to write the duration.
static const string durations_file = 
  "/home/adriana/Documents/uni/ppd2/src/results/parallel_duration.csv";
// The grade of the polynomials.
static const long long maximum_exponent = 5;
// The maximum coefficient of any grade of the polynomials.
static const short maximum_coefficient = 10; 

} // namespace

int main(int argc, char* argv[]) {
  // Initialize the MPI environment.
  MPI_Init(NULL, NULL);

  // Get the number of processes.
  unsigned int number_of_processes;
  MPI_Comm_size(MPI_COMM_WORLD, (int*)&number_of_processes);

  // Get the index of the process.
  int process_index;
  MPI_Comm_rank(MPI_COMM_WORLD, &process_index);

  if (process_index == 0) {
    const Polynomial first_polynomial = ReadFromFile(first_polynomial_file);
    const Polynomial second_polynomial = ReadFromFile(second_polynomial_file);
    
    const auto start = chrono::high_resolution_clock::now();
    const Polynomial result = ComputeMultiplicationParent(first_polynomial, 
      second_polynomial, number_of_processes);
    const auto end = chrono::high_resolution_clock::now();
    const auto duration = 
      chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << fixed << duration.count() << "\n";

    WriteLineToCsvFile(durations_file, {duration.count()});
    WriteToFile(result, result_file);

    const Polynomial validator_result = 
      ComputeMultiplication(first_polynomial, second_polynomial);
    WriteToFile(validator_result, validator_result_file);
    
    // Check whether the two results are identical aka whether the result using 
    // our parallel approach is correct.
    const bool are_identical = ComparePolynomials(result, validator_result);
    cout << (are_identical ? "CORRECT\n" : "INCORRECT\n");
  } else {
    ComputeMultiplicationChild(process_index);
  }

  MPI_Finalize();
  return 0;
}