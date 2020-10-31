#include "Vector3.hpp"

#include <cassert>
#include <cmath>

auto morpheus::Vector3::operator[](unsigned int i) -> float& { return (&x_)[i]; }

auto morpheus::Vector3::operator*=(float s) -> Vector3& {
  x_ *= s;
  y_ *= s;
  z_ *= s;
  return *this;
}

auto morpheus::Vector3::operator/=(float s) -> Vector3& {
  assert(s != 0);

  x_ /= s;
  y_ /= s;
  z_ /= s;
  return *this;
}

auto morpheus::Vector3::operator+=(const Vector3& v) -> Vector3& {
  x_ += v.x_;
  y_ += v.y_;
  z_ += v.z_;
  return *this;
}

auto morpheus::Vector3::operator-=(const Vector3& v) -> Vector3& {
  x_ -= v.x_;
  y_ -= v.y_;
  z_ -= v.z_;
  return *this;
}

auto morpheus::Vector3::normalize() -> Vector3& {
  *this /= this->magnitude();
  return *this;
}

auto morpheus::Vector3::dot(const Vector3& v) const -> float {
  return x_ * v.x() + y_ * v.y() + z_ * v.z();
}

auto morpheus::Vector3::project(const Vector3& v) -> Vector3& {
  *this = v * (this->dot(v) / v.dot(v));
  return *this;
}

auto morpheus::Vector3::reject(const Vector3& v) -> Vector3& {
  *this -= v * (this->dot(v) / v.dot(v));
  return *this;
}

auto morpheus::operator*(Vector3 v, float s) -> Vector3 {
  v *= s;
  return v;
}

auto morpheus::operator/(Vector3 v, float s) -> Vector3 {
  v /= s;
  return v;
}

auto morpheus::operator-(Vector3 v) -> Vector3 {
  v *= -1;
  return v;
}

auto morpheus::operator+(Vector3 a, const Vector3& b) -> Vector3 {
  a += b;
  return a;
}

auto morpheus::operator-(Vector3 a, const Vector3& b) -> Vector3 {
  a -= b;
  return a;
}

auto morpheus::normalize(Vector3 v) -> Vector3 {
  v.normalize();
  return v;
}

auto morpheus::cross(const Vector3& a, const Vector3& b) -> Vector3 {
  return {a.y() * b.z() - a.z() * b.y(),
          a.z() * b.x() - a.x() * b.z(),
          a.x() * b.y() - a.y() * b.x()};
}