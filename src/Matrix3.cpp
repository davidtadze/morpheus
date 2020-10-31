#include "Matrix3.hpp"

#include <initializer_list>

#include "Vector3.hpp"

morpheus::Matrix3::Matrix3(float n00, float n01, float n02,
                           float n10, float n11, float n12,
                           float n20, float n21, float n22) {
  n_[0][0] = n00; n_[0][1] = n10; n_[0][2] = n20;
  n_[1][0] = n01; n_[1][1] = n11; n_[1][2] = n21;
  n_[2][0] = n02; n_[2][1] = n12; n_[2][2] = n22;
}

morpheus::Matrix3::Matrix3(const initializer_list_float init_list) {
  assert(init_list.size() == 3);
  for (auto sublist : init_list) assert(sublist.size() == 3);

  int row = 0;
  int col = 0;
  for (auto sublist : init_list) {
    for (float element : sublist) {
      n_[col][row] = element;
      ++col;
    }
    col = 0;
    ++row;
  }
}

morpheus::Matrix3::Matrix3(const Vector3& a, const Vector3& b, const Vector3& c) {
  n_[0][0] = a.x(); n_[0][1] = a.y(); n_[0][2] = a.z();
  n_[1][0] = b.x(); n_[1][1] = b.y(); n_[1][2] = b.z();
  n_[2][0] = c.x(); n_[2][1] = c.y(); n_[2][2] = c.z();
}

auto morpheus::Matrix3::operator()(unsigned int i, unsigned int j) -> float& {
  return n_[j][i];
}

auto morpheus::Matrix3::operator[](unsigned int i) -> Vector3& {
  return reinterpret_cast<Vector3&>(n_[i]);
}

auto morpheus::Matrix3::operator*=(const Matrix3& m) -> Matrix3& {
  Matrix3 tmp;
  for (int j = 0; j < 3; ++j) {
    for (int k = 0; k < 3; ++k) {
      for (int i = 0; i < 3; ++i) {
        // swapped order from i, j, k to j, k, i
        // to minimize cache misses
        tmp(i, j) += (*this)(i, k) * m(k, j);
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
  for (int k = 0; k < 3; ++k) {
    for (int j = 0; j < 3; ++j) {
      for (int i = 0; i < 3; ++i) {
        // swapped order from i, j, k to k, j, i
        // to minimize cache misses
        tmp[j] += m(i, k) * v[k];
      }
    }
  }
  return tmp;
}
