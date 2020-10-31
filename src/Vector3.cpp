#include "Vector3.hpp"

#include <cassert>
#include <cmath>

using namespace morpheus;

auto Vector3::operator[](unsigned int i) -> float& {
  assert(i < 3);

  return (&x_)[i];
}

auto Vector3::operator*=(float s) -> Vector3& {
  x_ *= s;
  y_ *= s;
  z_ *= s;
  return *this;
}

auto Vector3::operator/=(float s) -> Vector3& {
  assert(s != 0);

  x_ /= s;
  y_ /= s;
  z_ /= s;
  return *this;
}

auto Vector3::operator+=(const Vector3& v) -> Vector3& {
  x_ += v.x_;
  y_ += v.y_;
  z_ += v.z_;
  return *this;
}

auto Vector3::operator-=(const Vector3& v) -> Vector3& {
  x_ -= v.x_;
  y_ -= v.y_;
  z_ -= v.z_;
  return *this;
}

auto Vector3::magnitude() const -> float {
  return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}

auto Vector3::normalize() -> Vector3& {
  *this /= this->magnitude();
  return *this;
}

auto operator*(Vector3 v, float s) -> Vector3 {
  v *= s;
  return v;
}

auto operator/(Vector3 v, float s) -> Vector3 {
  v /= s;
  return v;
}

auto operator-(Vector3 v) -> Vector3 {
  v *= -1;
  return v;
}

auto operator+(Vector3 a, const Vector3& b) -> Vector3 {
  a += b;
  return a;
}

auto operator-(Vector3 a, const Vector3& b) -> Vector3 {
  a -= b;
  return a;
}

auto magnitude(const Vector3& v) -> float {
  return v.magnitude();
}

auto normalize(Vector3 v) -> Vector3 {
  v.normalize();
  return v;
}