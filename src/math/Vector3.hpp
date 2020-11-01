#ifndef MORPHEUS_VECTOR3_HPP
#define MORPHEUS_VECTOR3_HPP

#include <cassert>

namespace morpheus {

struct Vector3 {
 private:
  float x_{0}, y_{0}, z_{0};

 public:
  Vector3() = default;
  Vector3(float x, float y, float z) : x_(x), y_(y), z_(z) {}

  auto x() const -> float { return x_; }
  auto y() const -> float { return y_; }
  auto z() const -> float { return z_; }

  auto operator[](unsigned int i) -> float&;
  auto operator[](unsigned int i) const -> const float& { return (*this)[i]; }

  auto operator*=(float s) -> Vector3&;
  auto operator/=(float s) -> Vector3&;

  auto operator+=(const Vector3& v) -> Vector3&;
  auto operator-=(const Vector3& v) -> Vector3&;

  auto magnitude() const -> float { return sqrt(x_ * x_ + y_ * y_ + z_ * z_); }
  auto normalize() -> Vector3&;

  auto dot(const Vector3& v) const -> float;

  auto project(const Vector3& v) -> Vector3&;
  auto reject(const Vector3& v) -> Vector3&;
};

auto operator*(Vector3 v, float s) -> Vector3;
auto operator/(Vector3 v, float s) -> Vector3;

auto operator-(Vector3 v) -> Vector3;

auto operator+(Vector3 a, const Vector3& b) -> Vector3;
auto operator-(Vector3 a, const Vector3& b) -> Vector3;

inline auto magnitude(const Vector3& v) -> float { return v.magnitude(); }
auto normalize(Vector3 v) -> Vector3;

inline auto dot(const Vector3& a, const Vector3& b) -> float { return a.dot(b); }
auto cross(const Vector3& a, const Vector3& b) -> Vector3;

inline auto project(Vector3 a, const Vector3& b) -> Vector3 { return a.project(b); }
inline auto reject(Vector3 a, const Vector3& b) -> Vector3 { return a.reject(b); }

}  // namespace morpheus

#endif  // MORPHEUS_VECTOR3_HPP