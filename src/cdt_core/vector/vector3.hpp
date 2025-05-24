//
//   ██████╗ ██████╗  ████████╗
//  ██╔════╝ ██╔══██╗ ╚══██╔══╝
//  ██║      ██║  ██║    ██║
//  ██║      ██║  ██║    ██║
//  ╚██████╗ ██████╔╝    ██║
//   ╚═════╝ ╚═════╝     ╚═╝
//

#pragma once

#include <cdt_config.hpp>

namespace cbt {

template <typename Real = double>
struct Vec3 {
    Real x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(Real x, Real y, Real z) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator*(Real scalar) const;
    Vec3 operator/(Real scalar) const;

    Vec3& operator+=(const Vec3& other);
    Vec3& operator-=(const Vec3& other);
    Vec3& operator*=(Real scalar);
    Vec3& operator/=(Real scalar);

    Real dot(const Vec3& other) const;
    Vec3 cross(const Vec3& other) const;
    Real norm() const;
};

template <typename Real>
inline Vec3<Real> Vec3<Real>::operator+(const Vec3& other) const {
    return Vec3(x + other.x, y + other.y, z + other.z);
}

template <typename Real>
inline Vec3<Real> Vec3<Real>::operator-(const Vec3& other) const {
    return Vec3(x - other.x, y - other.y, z - other.z);
}

template <typename Real>
inline Vec3<Real>& Vec3<Real>::operator+=(const Vec3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

template <typename Real>
inline Vec3<Real>& Vec3<Real>::operator-=(const Vec3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

template <typename Real>
inline Vec3<Real>& Vec3<Real>::operator*=(Real scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

template <typename Real>
inline Vec3<Real>& Vec3<Real>::operator/=(Real scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

template <typename Real>
inline Real Vec3<Real>::dot(const Vec3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

template <typename Real>
inline Vec3<Real> Vec3<Real>::cross(const Vec3& other) const {
    return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

template <typename Real>
inline Real Vec3<Real>::norm() const {
    return std::sqrt(dot(*this));
}

template <typename Real>
inline Vec3<Real> operator*(Real scalar, const Vec3<Real>& vec) {
    return Vec3<Real>(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

template <typename Real>
inline Vec3<Real> operator/(Real scalar, const Vec3<Real>& vec) {
    return Vec3<Real>(scalar / vec.x, scalar / vec.y, scalar / vec.z);
}

// Instantiate Vec3 for float and double types
template struct Vec3<float>;
template struct Vec3<double>;
template struct Vec3<long double>;

using Vec3f  = Vec3<float>;
using Vec3d  = Vec3<double>;
using Vec3ld = Vec3<long double>;

}  // end namespace cbt