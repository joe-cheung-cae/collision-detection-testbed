//
//   ██████╗ ██████╗  ████████╗
//  ██╔════╝ ██╔══██╗ ╚══██╔══╝
//  ██║      ██║  ██║    ██║
//  ██║      ██║  ██║    ██║
//  ╚██████╗ ██████╔╝    ██║
//   ╚═════╝ ╚═════╝     ╚═╝
//

#pragma once

namespace cbt {

template <typename Real = double>
struct Vec3 {
    Real x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(Real x, Real y, Real z) : x(x), y(y), z(z) {}

    Vec3 operator-(const Vec3& other) const { return Vec3(x - other.x, y - other.y, z - other.z); }

    Real dot(const Vec3& other) const { return x * other.x + y * other.y + z * other.z; }

    Vec3 cross(const Vec3& other) const {
        return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }
};

}  // end namespace cbt