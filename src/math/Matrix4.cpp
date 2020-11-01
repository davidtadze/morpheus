#include "Matrix4.hpp"

#include <initializer_list>

#include "Vector3.hpp"
#include "Vector4.hpp"

morpheus::Matrix4::Matrix4(const initializer_list_float init_list) {
  assert(init_list.size() == 4);
  for (auto sublist : init_list) assert(sublist.size() == 4);

  int row = 0;
  int col = 0;
  for (auto sublist : init_list) {
    for (float element : sublist) {
      // changed order from conventional row, col to col, row
      // to support subscript operator[] -> Vector4&
      n_[col][row] = element;
      ++col;
    }
    col = 0;
    ++row;
  }
}

morpheus::Matrix4::Matrix4(initializer_list_vector4 init_list) {
  assert(init_list.size() == 4);

  int row = 0;
  int col = 0;
  for (morpheus::Vector4 v : init_list) {
    for (int row = 0; row < 4; ++row) {
      // changed order from conventional row, col to col, row
      // to support subscript operator[] -> Vector4&
      n_[col][row] = v[row];
    }
    ++col;
  }
}

auto morpheus::Matrix4::operator()(int row, int col) -> float& {
  // changed order from conventional row, col to col, row
  // to support subscript operator[] -> Vector4&
  return n_[col][row];
}

auto morpheus::Matrix4::operator[](int col) -> Vector4& {
  // interface-wise column of a matrix4 is a vector4
  // but implementation-wise it must be a row to support subscript operator[] -> Vector4& 
  // (because of the way array is stored in memory)
  // so changed order from conventional row, col  to reversed col, row
  return reinterpret_cast<Vector4&>(n_[col]);
}

auto morpheus::Matrix4::operator*=(const Matrix4& m) -> Matrix4& {
  Matrix4 tmp;
  for (int col = 0; col < 4; ++col) {
    for (int k = 0; k < 4; ++k) {
      for (int row = 0; row < 4; ++row) {
        // changed order from row, col k to col, k, row
        // to minimize cache misses (because data is stored in col, row order)
        tmp(row, col) += (*this)(row, k) * m(k, col);
      }
    }
  }
  *this = tmp;
  return *this;
}

// auto morpheus::Matrix4::determinant() const -> float {
//   return ((*this)(0,0) * ((*this)(1,1) * (*this)(2,2) - (*this)(1,2) * (*this)(2,1))
// 	      + (*this)(0,1) * ((*this)(1,2) * (*this)(2,0) - (*this)(1,0) * (*this)(2,2))
// 	      + (*this)(0,2) * ((*this)(1,0) * (*this)(2,1) - (*this)(1,1) * (*this)(2,0)));
// }

auto morpheus::Matrix4::inverse() -> Matrix4& {
  const auto& a = reinterpret_cast<const Vector3&>((*this)[0]);
  const auto& b = reinterpret_cast<const Vector3&>((*this)[1]);
  const auto& c = reinterpret_cast<const Vector3&>((*this)[2]);
  const auto& d = reinterpret_cast<const Vector3&>((*this)[3]);

  const float& x = (*this)(3, 0);
  const float& y = (*this)(3, 1);
  const float& z = (*this)(3, 2);
  const float& w = (*this)(3, 3);

  Vector3 s = cross(a, b);
  Vector3 t = cross(c, d);
  Vector3 u = a * y - b * x;
  Vector3 v = c * w - d * z;

  float inv_det = 1.0F / (dot(s, v) + dot(t, u));
  s *= inv_det;
  t *= inv_det;
  u *= inv_det;
  v *= inv_det;

  Vector3 r0 = cross(b, v) + t * y;
  Vector3 r1 = cross(v, a) - t * x;
  Vector3 r2 = cross(d, u) + s * w;
  Vector3 r3 = cross(u, c) - s * z;

  *this =  {{r0.x(), r0.y(), r0.z(), -dot(b, t)},
            {r1.x(), r1.y(), r1.z(),  dot(a, t)},
            {r2.x(), r2.y(), r2.z(), -dot(d, s)},
            {r3.x(), r3.y(), r3.z(),  dot(c, s)}};
  
  return *this;
}

auto morpheus::operator*(Matrix4 a, const Matrix4& b) -> Matrix4 {
  a *= b;
  return a;
}

auto morpheus::operator*(Matrix4 m, Vector4 v) -> Vector4 {
  Vector4 tmp;
  for (int row = 0; row < 4; ++row) {
    for (int k = 0; k < 4; ++k) {
        tmp[row] += m(row, k) * v[k];
    }
  }
  return tmp;
}
