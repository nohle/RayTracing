#include "Vec3.h"
#include <assert.h>
#include <cmath>

Vec3 Vec3::Zero() {
  static Vec3 zero(0, 0, 0);
  return zero;
}

float Vec3::Dot(const Vec3& a, const Vec3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Vec3::Normalized(const Vec3& a) {
  return a / a.Norm();
}

Vec3::Vec3() = default;

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3::~Vec3() = default;

float Vec3::NormSquared() const {
  return x * x + y * y + z * z;
}

float Vec3::Norm() const {
  return std::sqrt(NormSquared());
}

Vec3 Vec3::operator-() const {
  return Vec3(-x, -y, -z);
}

Vec3 Vec3::operator+(const Vec3& a) const {
  return Vec3(x + a.x, y + a.y, z + a.z);
}

Vec3 Vec3::operator-(const Vec3& a) const {
  return Vec3(x - a.x, y - a.y, z - a.z);
}

Vec3 Vec3::operator*(float c) const {
  return Vec3(c * x, c * y, c * z);
}

Vec3 Vec3::operator/(float c) const {
  return (1 / c) * *this;
}

Vec3 operator*(float c, const Vec3& a) {
  return a * c;
}
