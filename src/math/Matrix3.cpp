#include "Matrix3.hpp"

#include <initializer_list>

#include "Vector3.hpp"

morpheus::Matrix3::Matrix3(const initializer_list_float init_list) {
  assert(init_list.size() == 3);
  for (auto sublist : init_list) assert(sublist.size() == 3);

  int row = 0;
  int col = 0;
  for (auto sublist : init_list) {
    for (float element : sublist) {
      // changed order from conventional row, col to col, row
      // to support subscript operator[] -> Vector3&
      n_[col][row] = element;
      ++col;
    }
    col = 0;
    ++row;
  }
}

morpheus::Matrix3::Matrix3(initializer_list_vector3 init_list) {
  assert(init_list.size() == 3);

  int row = 0;
  int col = 0;
  for (morpheus::Vector3 v : init_list) {
    for (int row = 0; row < 3; ++row) {
      // changed order from conventional row, col to col, row
      // to support subscript operator[] -> Vector3&
      n_[col][row] = v[row];
    }
    ++col;
  }
}

auto morpheus::Matrix3::operator()(int row, int col) -> float& {
  // changed order from conventional row, col to col, row
  // to support subscript operator[] -> Vector3&
  return n_[col][row];
}

auto morpheus::Matrix3::operator[](int col) -> Vector3& {
  // interface-wise column of a matrix3 is a vector3
  // but implementation-wise it must be a row to support subscript operator[] -> Vector3& 
  // (because of the way array is stored in memory)
  // so changed order from conventional row, col  to reversed col, row
  return reinterpret_cast<Vector3&>(n_[col]);
}

auto morpheus::Matrix3::operator*=(const Matrix3& m) -> Matrix3& {
  Matrix3 tmp;
  for (int col = 0; col < 3; ++col) {
    for (int k = 0; k < 3; ++k) {
      for (int row = 0; row < 3; ++row) {
        // changed order from row, col k to col, k, row
        // to minimize cache misses (because data is stored in col, row order)
        tmp(row, col) += (*this)(row, k) * m(k, col);
      }
    }
  }
  *this = tmp;
  return *this;
}

auto morpheus::operator*(Matrix3 a, const Matrix3& b) -> Matrix3 {
  a *= b;
  return a;
}

auto morpheus::operator*(Matrix3 m, Vector3 v) -> Vector3 {
  Vector3 tmp;
  for (int row = 0; row < 3; ++row) {
    for (int k = 0; k < 3; ++k) {
        tmp[row] += m(row, k) * v[k];
    }
  }
  return tmp;
}
