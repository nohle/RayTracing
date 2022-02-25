#pragma once
class Vec3 {
 public:
  static Vec3 Zero();

  static float Dot(const Vec3& a, const Vec3& b);
  static Vec3 Normalized(const Vec3& a);

  Vec3();
  Vec3(float x, float y, float z);
  ~Vec3();

  float NormSquared() const;
  float Norm() const;

  Vec3 operator-() const;
  Vec3 operator+(const Vec3& a) const;
  Vec3 operator-(const Vec3& a) const;
  Vec3 operator*(float c) const;
  Vec3 operator/(float c) const;

  float x = 0.0;
  float y = 0.0;
  float z = 0.0;
};

Vec3 operator*(float c, const Vec3& a);
