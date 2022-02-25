#include "Sphere.h"

#include <assert.h>
#include <algorithm>
#include <cmath>

Sphere::Sphere(const Vec3& center, float radius, const Color& color)
    : center_(center), radius_(radius) {
  assert(radius > 0);
  color_ = color;
}

Sphere::~Sphere() = default;

std::optional<float> Sphere::IntersectionDistance(const Ray& ray) const {
  // t*u + o := ray with origin o in direction u
  // c := center of sphere
  // r := radius of sphere
  // oc := vector from ray origin to sphere center, i.e., c - o
  // x := oc.u
  // y := oc^2 - r^2
  //
  // The roots of quadratic formula that give the intersection are
  //     t = x +- sqrt(x^2 - y)
  //
  // Note that
  //     t0 * t1 = y.
  //
  // To avoid catastrophic cancellation, define
  //     t0 := x + sign(x)*sqrt(x^2 - y)
  //     t1 := y / t0
  Vec3 oc = center_ - ray.origin();
  float x = Vec3::Dot(ray.unit_direction(), oc);
  float y = oc.NormSquared() - (radius_ * radius_);
  float discriminant = x * x - y;

  // No intersection.
  if (discriminant < 0.0f) {
    return std::nullopt;
  }
  // t0 or t1 < 0 is not physically possible. If one is, then ray origin is
  // inside sphere. If two are, then sphere is behind ray origin.
  float t0 = x > 0.0f ? x + std::sqrt(x * x - y) : x - std::sqrt(x * x - y);
  if (t0 < 0.0f) {
    return std::nullopt;
  }
  float t1 = y / t0;
  if (t1 < 0.0f) {
    return std::nullopt;
  }

  // Return the first intersection point.
  return std::min(t0, t1);
}