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

auto morpheus::Matrix3::determinant() const -> float {
  return ((*this)(0,0) * ((*this)(1,1) * (*this)(2,2) - (*this)(1,2) * (*this)(2,1))
	      + (*this)(0,1) * ((*this)(1,2) * (*this)(2,0) - (*this)(1,0) * (*this)(2,2))
	      + (*this)(0,2) * ((*this)(1,0) * (*this)(2,1) - (*this)(1,1) * (*this)(2,0)));
}

auto morpheus::Matrix3::inverse() -> Matrix3& {
  const Vector3& a = (*this)[0];
  const Vector3& b = (*this)[1];
  const Vector3& c = (*this)[2];

  Vector3 r0 = cross(b, c);
  Vector3 r1 = cross(c, a);
  Vector3 r2 = cross(a, b);

  float inv_det = 1.0F / dot(r2, c);

  *this = {{r0.x() * inv_det, r0.y() * inv_det, r0.z() * inv_det},
           {r1.x() * inv_det, r1.y() * inv_det, r1.z() * inv_det},
           {r2.x() * inv_det, r2.y() * inv_det, r2.z() * inv_det}};
  
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
