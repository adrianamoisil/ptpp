#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "utils/utils.h"

namespace {

using namespace std;
using namespace utils;

// The file whete to write the first polynomial.
static const string first_polynomial_file = "data/first_polynomial.txt"; 
// The file where to write the second polynomial.
static const string second_polynomial_file = "data/second_polynomial.txt";

} // namespace

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Invalid number of arguments.\n";
    exit(-1);
  }

  const unsigned long long maximum_exponent = atoll(argv[1]);
  const short maximum_coefficient = atoi(argv[2]);
  

  srand(time(0));
  GeneratePolynomial(
    first_polynomial_file, 
    maximum_exponent, 
    maximum_coefficient,
    /*allow_zero_as_coefficient=*/false);
  GeneratePolynomial(
    second_polynomial_file, 
    maximum_exponent, 
    maximum_coefficient,
    /*allow_zero_as_coefficient=*/false);
  return 0;
}
