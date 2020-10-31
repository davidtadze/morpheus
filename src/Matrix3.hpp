#ifndef MORPHEUS_MATRIX3_HPP
#define MORPHEUS_MATRIX3_HPP

#include <array>
#include <initializer_list>

#include "Vector3.hpp"

using array_3_3 = std::array<std::array<float, 3>, 3>;
using initializer_list_float = std::initializer_list<std::initializer_list<float>>;

namespace morpheus {

class Matrix3 {
 private:
  array_3_3 n_{};

 public:
  Matrix3() = default;
  Matrix3(float n00, float n01, float n02, 
          float n10, float n11, float n12,
          float n20, float n21, float n22);
  Matrix3(initializer_list_float init_list);
  Matrix3(const Vector3& a, const Vector3& b, const Vector3& c);

  auto operator()(unsigned int i, unsigned int j) -> float&;
  auto operator()(unsigned int i, unsigned int j) const -> const float& {
    return (*this)(i, j);
  }

  auto operator[](unsigned int i) -> Vector3&;
  auto operator[](unsigned int i) const -> const Vector3& { return (*this)[i]; }

  auto operator*=(const Matrix3& m) -> Matrix3&;
};

auto operator*(Matrix3 a, const Matrix3& b) -> Matrix3;
auto operator*(Matrix3 m, Vector3 v) -> Vector3;

}  // namespace morpheus

#endif  // MORPHEUS_MATRIX3_HPP