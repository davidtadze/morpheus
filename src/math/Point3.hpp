#ifndef MORPHEUS_POINT3_HPP
#define MORPHEUS_POINT3_HPP

#include "Vector3.hpp"

namespace morpheus {

class Point3: public Vector3 {
 public:
  Point3() = default;
	Point3(float a, float b, float c) : Vector3(a, b, c) {}

	auto operator=(const Vector3& v) -> Point3&;
};

auto operator+(const Point3& a, const Vector3& b) -> Point3;
auto operator-(const Point3& a, const Vector3& b) -> Point3;
auto operator-(const Point3& a, const Point3& b) -> Vector3;

}  // namespace morpheus

#endif  // MORPHEUS_POINT3_HPP