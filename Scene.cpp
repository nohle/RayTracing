#include "Scene.h"

#include <cstdint>

#include "Bitmap.h"
#include "Plane.h"
#include "Sphere.h"

namespace {
uint32_t kImageWidth = 1680;
uint32_t kImageHeight = 1680;
constexpr float z_camera = 2.0f;
}  // namespace

Scene::Scene() {
  // Scene in a cube from -1, +1 with (0,0,0) in the center of cube.
  shapes_.push_back(
      std::make_unique<Plane>(Vec3(0, 0, -1), Vec3(0, 0, 1), Color(0, 0, 255)));
  // Front of cube:
  // shapes_.push_back(std::make_unique<Plane>(Vec3(0, 0, 1), Vec3(0, 0, -1)));
  shapes_.push_back(
      std::make_unique<Plane>(Vec3(1, 0, 0), Vec3(-1, 0, 0), Color(0, 255, 0)));
  shapes_.push_back(
      std::make_unique<Plane>(Vec3(-1, 0, 0), Vec3(1, 0, 0), Color(0, 255, 0)));
  shapes_.push_back(
      std::make_unique<Plane>(Vec3(0, 1, 0), Vec3(0, -1, 0), Color(0, 255, 0)));
  shapes_.push_back(
      std::make_unique<Plane>(Vec3(0, -1, 0), Vec3(0, 1, 0), Color(0, 255, 0)));

  // Spheres:
  shapes_.push_back(
      std::make_unique<Sphere>(Vec3(0, 0, 0), 0.5f, Color(0, 255, 0)));
  shapes_.push_back(std::make_unique<Sphere>(Vec3(-0.5f, -0.5f, 0.5f), 0.25f,
                                             Color(0, 0, 255)));
  shapes_.push_back(std::make_unique<Sphere>(Vec3(-0.25f, -0.25f, 0.25f), 0.25f,
                                             Color(255, 0, 0)));
  shapes_.push_back(std::make_unique<Sphere>(Vec3(0.25f, 0.25f, -0.25f), 0.25f,
                                             Color(255, 0, 255)));
};

Scene::~Scene() = default;

void Scene::Draw() const {
  std::vector<std::vector<Bitmap::Pixel>> pixels(
      kImageHeight, std::vector<Bitmap::Pixel>(kImageWidth));
  for (size_t i = 0; i < kImageHeight; ++i) {
    for (size_t j = 0; j < kImageWidth; ++j) {
      // Origin of tracing ray in (-1,+1) scene space.
      Vec3 o = Vec3(2.0f * j / kImageWidth - 1.0f,
                    2.0f * i / kImageHeight - 1.0f, 1.0f);

      // Straight ray shoots in -z direction toward scene
      // Ray r = Ray(o, Vec3(0, 0, -1.0f));
      // std::optional<Hit> hit = FindClosestHit(r);

      // Shoot ray from camera origin to screen for perspective.
      Ray r = Ray::RayFromTo(Vec3(0.0f, 0.0f, z_camera), o);
      std::optional<Hit> hit = FindClosestHit(r);

      Color color;
      if (hit) {
        Vec3 p_hit = hit->distance * r.unit_direction() + r.origin();
        float z_hit = p_hit.z;

        color = hit->shape->color();
        color.red /= -2 * z_hit + 3;
        color.green /= -2 * z_hit + 3;
        color.blue /= -2 * z_hit + 3;
      }

      pixels[i][j].red = color.red;
      pixels[i][j].green = color.green;
      pixels[i][j].blue = color.blue;
    }
  }
  Bitmap::WriteToFile(pixels);
}

void Scene::DrawTest() const {
  std::vector<std::vector<Bitmap::Pixel>> pixels(
      kImageHeight, std::vector<Bitmap::Pixel>(kImageWidth));
  for (size_t i = 0; i < kImageHeight; ++i) {
    for (size_t j = 0; j < kImageWidth; ++j) {
      pixels[i][j].red = i * 255 / kImageHeight;
      pixels[i][j].green = 0;
      pixels[i][j].blue = j * 255 / kImageWidth;
    }
  }
  Bitmap::WriteToFile(pixels);
}

Scene::Hit::Hit() = default;

Scene::Hit::Hit(float distance, const Shape* shape)
    : distance(distance), shape(shape) {}

Scene::Hit::~Hit() = default;

std::optional<Scene::Hit> Scene::FindClosestHit(const Ray& ray) const {
  std::optional<Hit> hit;
  for (const auto& shape : shapes_) {
    std::optional<float> hit_distance = shape->IntersectionDistance(ray);
    if (!hit_distance)
      continue;

    if (!hit || hit_distance < hit->distance)
      hit = Hit(*hit_distance, shape.get());
  }
  return hit;
}
