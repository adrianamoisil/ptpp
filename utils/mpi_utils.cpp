#include "mpi_utils.h"

#include <mpi.h>

namespace utils {
namespace {

using namespace models;
using namespace std;

} // namespace

void MpiSendVector(
  const vector<long long>& data, 
  const int destination, 
  const int size_tag, 
  const int data_tag) {
  const int data_size = data.size();
  MPI_Send(&data_size, 1, MPI_INT, destination, size_tag, MPI_COMM_WORLD);
  MPI_Send(&data[0], data_size, MPI_LONG_LONG, destination, data_tag, 
    MPI_COMM_WORLD);
}

vector<long long> MpiRecvVector(
  const int source, 
  const int size_tag, 
  const int data_tag) {
  int data_size;
  MPI_Recv(&data_size, 1, MPI_INT, source, size_tag, MPI_COMM_WORLD, 
    MPI_STATUS_IGNORE);
  alignas(64) vector<long long> data(data_size);
  MPI_Recv(&data[0], data_size, MPI_LONG_LONG, source, data_tag, MPI_COMM_WORLD, 
    MPI_STATUS_IGNORE);
  return data;
}

void MpiSendPolynomial(
  const Polynomial& polynomial, 
  const int destination, 
  const int size_tag, 
  const int data_tag) {
  const int data_size = polynomial.GetDegree() + 1;
  MPI_Send(&data_size, 1, MPI_INT, destination, size_tag, MPI_COMM_WORLD);
  if (polynomial.IsNull()) {
    const vector<long long> coefficients_for_null_polynomial = {0};
    MPI_Send(&coefficients_for_null_polynomial[0], data_size, MPI_LONG_LONG, 
      destination, data_tag, MPI_COMM_WORLD);
    return;
  }
  const void* coefficients_pointer = polynomial.GetCoefficientsPointer();
  MPI_Send(coefficients_pointer, data_size, MPI_LONG_LONG, destination, data_tag, 
    MPI_COMM_WORLD);
}

Polynomial MpiRecvPolynomial(
  const int source, 
  const int size_tag, 
  const int data_tag) {
  int data_size;
  alignas(64) vector<long long> coefficients = 
    MpiRecvVector(source, size_tag, data_tag);
  return Polynomial(coefficients);
}

} // namespace utils 