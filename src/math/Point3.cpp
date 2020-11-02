#include "Point3.hpp"

auto morpheus::Point3::operator=(const Vector3& v) -> Point3& {
  x_ = v.x();
  y_ = v.y();
  z_ = v.z();
  return *this;
}

auto morpheus::operator+(const Point3& a, const Vector3& b) -> Point3 {
  return {a.x() + b.x(), a.y() + b.y(), a.z() + b.z()};
}

auto morpheus::operator-(const Point3& a, const Vector3& b) -> Point3 {
  return {a.x() - b.x(), a.y() - b.y(), a.z() - b.z()};
}

auto morpheus::operator-(const Point3& a, const Point3& b) -> Vector3 {
  return {a.x() - b.x(), a.y() - b.y(), a.z() - b.z()};
}
