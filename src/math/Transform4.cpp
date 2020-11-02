#include "Transform4.hpp"

#include "Vector3.hpp"
#include "Point3.hpp"

morpheus::Transform4::Transform4(initializer_list_float init_list) {
  assert(init_list.size() == 3);
  for (auto sublist : init_list) assert(sublist.size() == 4);

  int row = 0;
  int col = 0;
  for (auto sublist : init_list) {
    for (float element : sublist) {
      // changed order from conventional row, col to col, row
      // to support subscript operator[] -> Vector3&
      n_[col][row] = element;
      ++col;
    }
    col = 0;
    ++row;
  }
  n_[0][3] = n_[1][3] = n_[2][3] = 0.0F; n_[3][3] = 1.0F;
}

morpheus::Transform4::Transform4(const Vector3& a, const Vector3& b, const Vector3& c, const Point3& p) {
  n_[0][0] = a.x(); n_[0][1] = a.y(); n_[0][2] = a.z();
  n_[1][0] = b.x(); n_[1][1] = b.y(); n_[1][2] = b.z();
  n_[2][0] = c.x(); n_[2][1] = c.y(); n_[2][2] = c.z();
  n_[3][0] = p.x(); n_[3][1] = p.y(); n_[3][2] = p.z();

  n_[0][3] = n_[1][3] = n_[2][3] = 0.0F; n_[3][3] = 1.0F;
}

auto morpheus::Transform4::operator[](int j) -> Vector3& {
  return *reinterpret_cast<Vector3*>(n_[j].data());
}

auto morpheus::Transform4::operator[](int j) const -> const Vector3& {
  return *reinterpret_cast<const Vector3*>(n_[j].data());
}

auto morpheus::Transform4::get_translation() const -> const Point3&{
  return *reinterpret_cast<const Point3*>(n_[3].data());
}

void morpheus::Transform4::set_translation(const Point3& p) {
  n_[3][0] = p.x();
  n_[3][1] = p.y();
  n_[3][2] = p.z();
}

auto morpheus::inverse(const Transform4& h) -> Transform4 {
  const Vector3& a = h[0];
  const Vector3& b = h[1];
  const Vector3& c = h[2];
  const Vector3& d = h[3];

  Vector3 s = cross(a, b);
  Vector3 t = cross(c, d);

  float inv_det = 1.0F / dot(s, c);

  s *= inv_det;
  t *= inv_det;
  Vector3 v = c * inv_det;

  Vector3 r0 = cross(b, v);
  Vector3 r1 = cross(v, a);

  return {{ r0.x(), r0.y(), r0.z(), -dot(b, t)    },
          { r1.x(), r1.y(), r1.z(), dot(a, t)     },
          { s.x(),  s.y(),  s.z(),  -dot(d, s)    }};
}

auto morpheus::operator*(const Transform4& a, const Transform4& b) -> Transform4 {
  return {
    { a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0),
      a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1),
      a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2),
      a(0, 0) * b(0, 3) + a(0, 1) * b(1, 3) + a(0, 2) * b(2, 3) + a(0, 3) },
    { a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0),
      a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1),
      a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2),
      a(1, 0) * b(0, 3) + a(1, 1) * b(1, 3) + a(1, 2) * b(2, 3) + a(1, 3) },
    { a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0),
      a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1),
      a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2),
      a(2, 0) * b(0, 3) + a(2, 1) * b(1, 3) + a(2, 2) * b(2, 3) + a(2, 3)}
  };
}

auto morpheus::operator*(const Transform4& h, const Vector3& v) -> Vector3 {
  return { h(0, 0) * v.x() + h(0, 1) * v.y() + h(0, 2) * v.z(),
           h(1, 0) * v.x() + h(1, 1) * v.y() + h(1, 2) * v.z(),
           h(2, 0) * v.x() + h(2, 1) * v.y() + h(2, 2) * v.z() };
}

auto morpheus::operator*(const Transform4& h, const Point3& p) -> Point3 {
  return { h(0, 0) * p.x() + h(0, 1) * p.y() + h(0, 2) * p.z() + h(0, 3),
           h(1, 0) * p.x() + h(1, 1) * p.y() + h(1, 2) * p.z() + h(1, 3),
           h(2, 0) * p.x() + h(2, 1) * p.y() + h(2, 2) * p.z() + h(2, 3) };
}