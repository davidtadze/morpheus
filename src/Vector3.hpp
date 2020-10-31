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

  auto magnitude() const -> float;

  auto normalize() -> Vector3&;
  auto normalize() const -> const Vector3& { return this->normalize(); }
};

auto operator*(Vector3 v, float s) -> Vector3;
auto operator/(Vector3 v, float s) -> Vector3;

auto operator-(Vector3 v) -> Vector3;

auto operator+(Vector3 a, const Vector3& b) -> Vector3;
auto operator-(Vector3 a, const Vector3& b) -> Vector3;

auto magnitude(const Vector3& v) -> float;

auto normalize(Vector3 v) -> Vector3;

}  // namespace morpheus

#endif  // MORPHEUS_VECTOR3_HPP