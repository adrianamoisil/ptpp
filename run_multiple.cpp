#include <chrono>
#include <thread>
#include <iostream>
#include <string>

using namespace std;

static const string kPolynomialsGeneratorExe = "exe/polynomials_generator.exe"; 

int main(int argc, char* argv[]) {
  if (argc != 5) {
    cerr << "Invalid number of arguments.\n";
    exit(-1);
  }

  const char* command = argv[1];
  const int number_of_runs = atoi(argv[2]);
  const unsigned long long maximum_exponent = atoll(argv[3]);
  const short maximum_coefficient = atoi(argv[4]);

  cout << "Command to run: " << command << "\n";
  cout << "Number of runs: " << number_of_runs << "\n";
  cout << "maximum_exponent: " << maximum_exponent << "\n";
  cout << "maximum_coefficient: " << maximum_coefficient << "\n";

  const auto polynomial_generator_command = kPolynomialsGeneratorExe + " "
    + to_string(maximum_exponent) + " " + to_string(maximum_coefficient);

  for (int run_number = 1; run_number <= number_of_runs; ++run_number) {
    cout << "==================================================\n";
    cout << "Run number: " << run_number << "\n";
    // Generate polynomials.
    system(polynomial_generator_command.c_str());
    cout << "==================================================\n";
    system(command);
    cout << "==================================================\n";
  }

  return 0;
}