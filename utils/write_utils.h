#ifndef UTILS_WRITE_UTILS_H
#define UTILS_WRITE_UTILS_H

#include <string>
#include <vector>

#include "../models/polynomial.h"

namespace utils {

// Writes a polynomial from the given file.
// TODO: info about format
void WriteToFile(const models::Polynomial& polynomial,
  const std::string& filename);

void WriteToStdout(const models::Polynomial& polynomial);

void WriteLineToCsvFile(const std::string& filename, 
  const std::vector<long long>& values);

} // namespace utils 

#endif // UTILS_WRITE_UTILS_H
