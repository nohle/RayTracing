#pragma once

#include <optional>

#include "Ray.h"
#include "Shape.h"
#include "Vec3.h"

class Sphere : public Shape {
 public:
  Sphere(const Vec3& center, float radius, const Color& color);
  ~Sphere() override;

  // Shape:
  std::optional<float> IntersectionDistance(const Ray& ray) const override;

  const Vec3& center() const { return center_; }
  float radius() const { return radius_; }

 private:
  const Vec3 center_;
  const float radius_;
};
