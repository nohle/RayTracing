#pragma once

#include "Vec3.h"

class Ray {
 public:
  static Ray RayFromTo(Vec3 from, Vec3 to);

  Ray(Vec3 origin, Vec3 direction);
  ~Ray();

  const Vec3& origin() const { return origin_; }
  const Vec3& unit_direction() const { return unit_direction_; }

 private:
  const Vec3 origin_;
  const Vec3 unit_direction_;
};
