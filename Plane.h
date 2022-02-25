#pragma once

#include <optional>

#include "Ray.h"
#include "Shape.h"
#include "Vec3.h"

class Plane : public Shape {
 public:
  Plane(const Vec3& point, const Vec3& normal, const Color& color);
  ~Plane() override;

  // Shape:
  std::optional<float> IntersectionDistance(const Ray& ray) const override;

 private:
  const Vec3 point_;
  const Vec3 normal_;
};
