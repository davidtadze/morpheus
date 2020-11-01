#ifndef MORPHEUS_VECTOR4_HPP
#define MORPHEUS_VECTOR4_HPP

#include <cmath>

namespace morpheus {

class Vector4 {
 private:
  float x_{0}, y_{0}, z_{0}, w_{0};
public:
  Vector4() = default;
  Vector4(float x, float y, float z) : x_(x), y_(y), z_(z) {}

  auto x() const -> float { return x_; }
  auto y() const -> float { return y_; }
  auto z() const -> float { return z_; }
  auto w() const -> float { return w_; }

  auto operator[](unsigned int i) -> float&;
  auto operator[](unsigned int i) const -> const float& { return (*this)[i]; }

  auto operator*=(float s) -> Vector4&;
  auto operator/=(float s) -> Vector4&;

  auto operator+=(const Vector4& v) -> Vector4&;
  auto operator-=(const Vector4& v) -> Vector4&;

  auto magnitude() const -> float { return sqrt(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_); }
  auto normalize() -> Vector4&;

  auto dot(const Vector4& v) const -> float;

  auto project(const Vector4& v) -> Vector4&;
  auto reject(const Vector4& v) -> Vector4&;
};

auto operator*(Vector4 v, float s) -> Vector4;
auto operator/(Vector4 v, float s) -> Vector4;

auto operator-(Vector4 v) -> Vector4;

auto operator+(Vector4 a, const Vector4& b) -> Vector4;
auto operator-(Vector4 a, const Vector4& b) -> Vector4;

inline auto magnitude(const Vector4& v) -> float { return v.magnitude(); }
auto normalize(Vector4 v) -> Vector4;

inline auto dot(const Vector4& a, const Vector4& b) -> float { return a.dot(b); }

inline auto project(Vector4 a, const Vector4& b) -> Vector4 { return a.project(b); }
inline auto reject(Vector4 a, const Vector4& b) -> Vector4 { return a.reject(b); }

}  // namespace morpheus

#endif  // MORPHEUS_VECTOR4_HPP