#include "Vector4.hpp"

#include <cassert>
#include <cmath>

auto morpheus::Vector4::operator[](unsigned int i) -> float& { return (&x_)[i]; }

auto morpheus::Vector4::operator*=(float s) -> Vector4& {
  x_ *= s;
  y_ *= s;
  z_ *= s;
  w_ *= s;
  return *this;
}

auto morpheus::Vector4::operator/=(float s) -> Vector4& {
  assert(s != 0);

  x_ /= s;
  y_ /= s;
  z_ /= s;
  w_ /= s;
  return *this;
}

auto morpheus::Vector4::operator+=(const Vector4& v) -> Vector4& {
  x_ += v.x_;
  y_ += v.y_;
  z_ += v.z_;
  w_ += v.w_;
  return *this;
}

auto morpheus::Vector4::operator-=(const Vector4& v) -> Vector4& {
  x_ -= v.x_;
  y_ -= v.y_;
  z_ -= v.z_;
  w_ += v.w_;
  return *this;
}

auto morpheus::Vector4::normalize() -> Vector4& {
  *this /= this->magnitude();
  return *this;
}

auto morpheus::Vector4::dot(const Vector4& v) const -> float {
  return x_ * v.x() + y_ * v.y() + z_ * v.z() + w_ * v.w();
}

auto morpheus::Vector4::project(const Vector4& v) -> Vector4& {
  *this = v * (this->dot(v) / v.dot(v));
  return *this;
}

auto morpheus::Vector4::reject(const Vector4& v) -> Vector4& {
  *this -= v * (this->dot(v) / v.dot(v));
  return *this;
}

auto morpheus::operator*(Vector4 v, float s) -> Vector4 {
  v *= s;
  return v;
}

auto morpheus::operator/(Vector4 v, float s) -> Vector4 {
  v /= s;
  return v;
}

auto morpheus::operator-(Vector4 v) -> Vector4 {
  v *= -1;
  return v;
}

auto morpheus::operator+(Vector4 a, const Vector4& b) -> Vector4 {
  a += b;
  return a;
}

auto morpheus::operator-(Vector4 a, const Vector4& b) -> Vector4 {
  a -= b;
  return a;
}

auto morpheus::normalize(Vector4 v) -> Vector4 {
  v.normalize();
  return v;
}