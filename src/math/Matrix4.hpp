#ifndef MORPHEUS_MATRIX4_HPP
#define MORPHEUS_MATRIX4_HPP

#include <array>
#include <initializer_list>

#include "Vector4.hpp"

using array_float_4_4 = std::array<std::array<float, 4>, 4>;
using initializer_list_float = std::initializer_list<std::initializer_list<float>>;
using initializer_list_vector4 = std::initializer_list<morpheus::Vector4>;

namespace morpheus {

class Matrix4 {
 private:
  array_float_4_4 n_{};

 public:
  Matrix4() = default;
  Matrix4(initializer_list_float init_list);
  Matrix4(initializer_list_vector4 init_list);

  auto operator()(int row, int col) -> float&;
  auto operator()(int row, int col) const -> const float& { return (*this)(row, col); }

  auto operator[](int col) -> Vector4&;
  auto operator[](int col) const -> const Vector4& { return (*this)[col]; }

  auto operator*=(const Matrix4& m) -> Matrix4&;

  // auto determinant() const -> float;
  auto inverse() -> Matrix4&;
};

auto operator*(Matrix4 a, const Matrix4& b) -> Matrix4;
auto operator*(Matrix4 m, Vector4 v) -> Vector4;

// inline auto determinant(const Matrix4& m) -> float { return m.determinant(); }
inline auto inverse(Matrix4 m) -> Matrix4 { return m.inverse(); }

}  // namespace morpheus

#endif  // MORPHEUS_MATRIX4_HPP