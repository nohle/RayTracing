#pragma once

#include <optional>

#include "Color.h"
#include "Ray.h"

class Shape {
 public:
  virtual ~Shape();

  virtual std::optional<float> IntersectionDistance(const Ray& ray) const = 0;

  const Color& color() const { return color_; }

 protected:
  Color color_;
};
