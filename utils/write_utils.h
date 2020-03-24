#ifndef UTILS_WRITE_UTILS_H
#define UTILS_WRITE_UTILS_H

#include <string>
#include <vector>

#include "../models/polynomial.h"

namespace utils {

// Writes a polynomial to the given file.
void WriteToFile(const models::Polynomial& polynomial,
  const std::string& filename);

// Writes a polynomial to standard output.
void WriteToStdout(const models::Polynomial& polynomial);

// Writes a vector to the given csv file.
void WriteLineToCsvFile(const std::string& filename, 
  const std::vector<long long>& values);

} // namespace utils 

#endif // UTILS_WRITE_UTILS_H
