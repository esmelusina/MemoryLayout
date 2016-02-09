#pragma once
#include <cmath>
#include <cassert>
#include <cfloat>
#include "Vector2.h"

struct Vector3
{
    union
    {
        float v[3];
        struct { float x, y, z; };
        Vector2 xy;
    };
    Vector3() {}
    Vector3(float a_x, float a_y, float a_z)
        : x(a_x), y(a_y), z(a_z) {}

    float magnitude() const { return sqrtf(x*x + y*y + z*z); }

    float &operator[](unsigned idx)       { return v[idx]; }
    float  operator[](unsigned idx) const { return v[idx]; }
};

// Direction Between Vectors:
//(A-B).normal()
// Distance Between Vectors:
//(A-B).magnitude()

inline Vector3 operator-(const Vector3  &lhs, const Vector3 &rhs)
{
    return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z-rhs.z);
}

inline Vector3 operator/(const Vector3 &lhs, float rhs)
{
    return Vector3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

inline Vector3 operator*(const Vector3 &lhs, float rhs)
{
    return{lhs.x*rhs,lhs.y*rhs,lhs.z*rhs };
}

// Dot production tells us how much one vector extends
// in the direction of another vector
inline float dot(const Vector3 &lhs, const Vector3 &rhs)
{
    return lhs.x * rhs.x + rhs.y * lhs.y + rhs.z*lhs.z;
}

//#define EPSILON 0.0001f

inline bool operator==(const Vector3 &lhs, const Vector3 &rhs)
{
    // return lhs.x == rhs.x && lhs.y == rhs.y;
    return
        rhs.x - FLT_EPSILON < lhs.x && lhs.x < rhs.x + FLT_EPSILON &&
        rhs.y - FLT_EPSILON < lhs.y && lhs.y < rhs.y + FLT_EPSILON &&
        rhs.z - FLT_EPSILON < lhs.z && lhs.z < rhs.z + FLT_EPSILON;

    //return fabsf(rhs.x - lhs.x) < FLT_EPSILON &&
    //       fabsf(rhs.y - lhs.y) < FLT_EPSILON;
}

inline Vector3 normal(const Vector3 &a)
{
    //assert(magnitude() != 0 && "Divide by Zero");
    return a / a.magnitude();
}