#ifndef MORPHEUS_MATRIX3_HPP
#define MORPHEUS_MATRIX3_HPP

#include <array>
#include <initializer_list>

#include "Vector3.hpp"

using array_float_3_3 = std::array<std::array<float, 3>, 3>;
using initializer_list_float = std::initializer_list<std::initializer_list<float>>;
using initializer_list_vector3 = std::initializer_list<morpheus::Vector3>;

namespace morpheus {

class Matrix3 {
 private:
  array_float_3_3 n_{};

 public:
  Matrix3() = default;
  Matrix3(initializer_list_float init_list);
  Matrix3(initializer_list_vector3 init_list);

  auto operator()(int row, int col) -> float&;
  auto operator()(int row, int col) const -> const float& { return (*this)(row, col); }

  auto operator[](int col) -> Vector3&;
  auto operator[](int col) const -> const Vector3& { return (*this)[col]; }

  auto operator*=(const Matrix3& m) -> Matrix3&;

  auto determinant() const -> float;
  auto inverse() -> Matrix3&;
};

auto operator*(Matrix3 a, const Matrix3& b) -> Matrix3;
auto operator*(Matrix3 m, Vector3 v) -> Vector3;

inline auto determinant(const Matrix3& m) -> float { return m.determinant(); }
inline auto inverse(Matrix3 m) -> Matrix3 { return m.inverse(); }

auto make_rotation_matrix_x(float t) -> Matrix3;
auto make_rotation_matrix_y(float t) -> Matrix3;
auto make_rotation_matrix_z(float t) -> Matrix3;
auto make_rotation_matrix(float t, const Vector3& a) -> Matrix3;
auto make_reflection_matrix(const Vector3& a) -> Matrix3;
auto make_involution_matrix(const Vector3& a) -> Matrix3;
auto make_scale_matrix(float sx, float sy, float sz) -> Matrix3;
auto make_scale_matrix(float s, const Vector3& a) -> Matrix3;
auto make_skew_matrix(float t, const Vector3& a, const Vector3& b) -> Matrix3;

}  // namespace morpheus

#endif  // MORPHEUS_MATRIX3_HPP