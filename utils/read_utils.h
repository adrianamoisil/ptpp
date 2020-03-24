#ifndef UTILS_READ_UTILS_H
#define UTILS_READ_UTILS_H

#include <string>

#include "../models/polynomial.h"

namespace utils {

// Reads a polynomial from the given file.
models::Polynomial ReadFromFile(const std::string& filename);

} // namespace utils 

#endif // UTILS_READ_UTILS_H
