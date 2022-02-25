#include "Plane.h"

namespace {
const float epsilon = 0.0001f;
bool IsNearlyEqual(float x, float y) {
  return std::abs(x - y) <= epsilon * std::abs(x);
}
}  // namespace

Plane::Plane(const Vec3& point, const Vec3& normal, const Color& color)
    : point_(point), normal_(Vec3::Normalized(normal)) {
  color_ = color;
}

Plane::~Plane() = default;

std::optional<float> Plane::IntersectionDistance(const Ray& ray) const {
  // Ray and plane are parallel.
  float a = Vec3::Dot(normal_, ray.unit_direction());
  if (IsNearlyEqual(a, 0.0f))
    return std::nullopt;

  float t = Vec3::Dot(normal_, point_ - ray.origin()) / a;

  // Intersection is in opposite direction as the ray.
  if (t <= 0.0f)
    return std::nullopt;

  return t;
}
