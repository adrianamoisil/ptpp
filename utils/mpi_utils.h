#ifndef UTILS_MPI_UTILS_H
#define UTILS_MPI_UTILS_H

#include <vector>
#include <map>

#include "../models/polynomial.h"

namespace utils {

// Sends a vector to another process using MPI_Send.
void MpiSendVector(
  const std::vector<long long>& data, 
  const int destination, 
  const int size_tag, 
  const int data_tag);

// Receives a vector from another process using MPI_Recv.
std::vector<long long> MpiRecvVector(
  const int source, 
  const int size_tag, 
  const int data_tag);

// Sends a Polynomial to another process using MPI_Send.
void MpiSendPolynomial(
  const models::Polynomial& polynomial, 
  const int destination, 
  const int size_tag, 
  const int data_tag);

// Receives a Polynomial from another process using MPI_Recv.
models::Polynomial MpiRecvPolynomial(
  const int source, 
  const int size_tag, 
  const int data_tag);

} // namespace utils 

#endif // UTILS_MPI_UTILS_H
