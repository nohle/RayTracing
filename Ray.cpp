#include "Ray.h"

Ray Ray::RayFromTo(Vec3 from, Vec3 to) {
  return Ray(from, to - from);
}

Ray::Ray(Vec3 origin, Vec3 direction)
    : origin_(origin), unit_direction_(Vec3::Normalized(direction)) {}

Ray::~Ray() = default;
