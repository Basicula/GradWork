#pragma once

#include <Vector.h>

class Camera
  {
  public:
    // fov in degrees
    // aspect = width / height
    // focusDist - distance from "camera" to generated(rendered) picture
    Camera(
      const Vector3d& i_lookFrom,
      const Vector3d& i_lookAt,
      const Vector3d& i_up,
      double i_fov,
      double i_aspect,
      double i_focusDist);

    Vector3d GetLocation() const;
    void SetLocation(const Vector3d& i_location);

    Vector3d GetDirection(double i_u, double i_v) const;

  private:
    Vector3d m_location;
    Vector3d m_direction;
    Vector3d m_up;
    Vector3d m_right;
    Vector3d m_corner;
    Vector3d m_u;
    Vector3d m_v;

    double m_fov;
    double m_aspect;
    double m_focusDistance;
  };

inline Vector3d Camera::GetLocation() const
  {
  return m_location;
  }

inline void Camera::SetLocation(const Vector3d& i_location)
  {
  m_location = i_location;
  }

inline Vector3d Camera::GetDirection(double i_u, double i_v) const
  {
  return (m_u * i_u + m_v * i_v - m_corner).Normalized();
  }