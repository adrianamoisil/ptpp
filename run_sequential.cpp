#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <mpi.h>

#include "models/polynomial.h"
#include "operations/sequential_operations.h"
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
  "/home/adriana/Documents/uni/ppd2/src/results/sequential_result.txt";
// The csv file where to write the duration.
static const string durations_file = 
  "/home/adriana/Documents/uni/ppd2/src/results/sequential_duration.csv";

} // namespace

int main(int argc, char* argv[]) {
  const Polynomial first_polynomial = ReadFromFile(first_polynomial_file);
  const Polynomial second_polynomial = ReadFromFile(second_polynomial_file);
  
  const auto start = chrono::high_resolution_clock::now();
  const Polynomial result = ComputeMultiplication(first_polynomial, second_polynomial);
  const auto end = chrono::high_resolution_clock::now();
  const auto duration = 
    chrono::duration_cast<chrono::nanoseconds>(end - start);
  cout << fixed << duration.count() << "\n";

  WriteLineToCsvFile(durations_file, {duration.count()});
  WriteToFile(result, result_file);

  return 0;
}