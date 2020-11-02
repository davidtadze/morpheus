#ifndef MORPHEUS_TRANSFORM4_HPP
#define MORPHEUS_TRANSFORM4_HPP

#include "Matrix4.hpp"
#include "Vector3.hpp"
#include "Point3.hpp"

using initializer_list_float = std::initializer_list<std::initializer_list<float>>;

namespace morpheus {

class Transform4: public Matrix4 {
 public:
  Transform4() = default;
  Transform4(initializer_list_float init_list);
  Transform4(const Vector3& a, const Vector3& b, const Vector3& c, const Point3& p);

  auto operator[](int j) -> Vector3&;
  auto operator[](int j) const -> const Vector3&;

  auto get_translation() const -> const Point3&;
  void set_translation(const Point3& p);
};

auto inverse(const Transform4& h) -> Transform4;

auto operator*(const Transform4& a, const Transform4& b) -> Transform4;
auto operator*(const Transform4& h, const Vector3& v) -> Vector3;
auto operator*(const Transform4& h, const Point3& p) -> Point3;

}  // namespace morpheus

#endif  // MORPHEUS_TRANSFORM4_HPP