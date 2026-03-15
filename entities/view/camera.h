/*
 * camera.h
 *
 * Rotation-matrix-based orbital camera (patched for MeshGit2).
 * Orientation: right, up, back (rows of world-to-camera matrix).
 */

#pragma once

#include <algorithm>
#include <cmath>
#include "utils/mathematics.h"
#include "utils/algorithms.h"
#include "config.h"

class Camera {
public:

    Vec3 right;
    Vec3 up;
    Vec3 back;

    float zoom;
    float pan_x;
    float pan_y;

    Camera()
        : right(1, 0, 0), up(0, 1, 0), back(0, 0, 1),
          zoom(std::clamp(1.0f, ZOOM_MIN, ZOOM_MAX)),
          pan_x(0.0f), pan_y(0.0f) {}

    explicit Camera(float z)
        : right(1, 0, 0), up(0, 1, 0), back(0, 0, 1),
          zoom(std::clamp(z, ZOOM_MIN, ZOOM_MAX)),
          pan_x(0.0f), pan_y(0.0f) {}

    Camera(float azimuth, float altitude, float z)
        : zoom(std::clamp(z, ZOOM_MIN, ZOOM_MAX)),
          pan_x(0.0f), pan_y(0.0f)
    {
        set_from_angles(azimuth, altitude);
    }

    void set_from_angles(float azimuth, float altitude)
    {
        const float ca = std::cos(altitude), sa = std::sin(altitude);
        const float cy = std::cos(azimuth),  sy = std::sin(azimuth);
        right = Vec3(cy,       0.0f, -sy);
        up    = Vec3(sa * sy,  ca,    sa * cy);
        back  = Vec3(ca * sy, -sa,    ca * cy);
    }

    [[nodiscard]] Vec3 view_transform(const Vec3 &v) const
    {
        return Vec3(Vec3::dot(right, v),
                    Vec3::dot(up, v),
                    Vec3::dot(back, v));
    }

    void orbit_yaw(float radians)
    {
        const float c = std::cos(radians), s = std::sin(radians);
        const Vec3 nr = right * c + back * s;
        const Vec3 nb = right * (-s) + back * c;
        right = nr;
        back  = nb;
    }

    void orbit_pitch(float radians)
    {
        const float c = std::cos(radians), s = std::sin(radians);
        const Vec3 nu = up * c - back * s;
        const Vec3 nb = up * s + back * c;
        up   = nu;
        back = nb;
    }

    void roll_view(float radians)
    {
        const float c = std::cos(radians), s = std::sin(radians);
        const Vec3 nr = right * c - up * s;
        const Vec3 nu = right * s + up * c;
        right = nr;
        up    = nu;
    }

    void rotate_left(float degree = ANGLE_STEP)  { orbit_yaw(deg2rad(degree)); }
    void rotate_right(float degree = ANGLE_STEP) { orbit_yaw(-deg2rad(degree)); }
    void rotate_up(float degree = ANGLE_STEP)    { orbit_pitch(deg2rad(degree)); }
    void rotate_down(float degree = ANGLE_STEP)  { orbit_pitch(-deg2rad(degree)); }

    void zoom_in(float step = ZOOM_STEP)  { zoom = std::min(zoom + step, ZOOM_MAX); }
    void zoom_out(float step = ZOOM_STEP) { zoom = std::max(zoom - step, ZOOM_MIN); }

    [[nodiscard]] float get_azimuth() const { return std::atan2(back.x, back.z); }
    [[nodiscard]] float get_altitude() const { return std::asin(std::clamp(-back.y, -1.0f, 1.0f)); }

    void orthonormalize()
    {
        back  = back.normalize();
        right = (right - back * Vec3::dot(right, back)).normalize();
        up    = Vec3::cross(back, right);
    }
};
