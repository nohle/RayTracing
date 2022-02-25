#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "Shape.h"

class Scene {
 public:
  Scene();
  ~Scene();

  void Draw() const;
  void DrawTest() const;

 private:
  struct Hit {
    Hit();
    Hit(float distance, const Shape* shape);
    ~Hit();

    float distance;
    const Shape* shape;
  };
  std::optional<Hit> FindClosestHit(const Ray& ray) const;

  std::vector<std::unique_ptr<Shape>> shapes_;
};
