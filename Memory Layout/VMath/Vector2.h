#pragma once
#include <cmath>
#include <cassert>
#include <cfloat>

struct Vector2
{
    union
    {
        struct { float x, y; };
        float v[2];
    };
    Vector2() {}
    Vector2(float a_x, float a_y)
        : x(a_x), y(a_y) {}

    float magnitude() const { return sqrtf(x*x + y*y); }

    float angle() const { return atan2f(y, x); }

    float &operator[](unsigned idx) { return v[idx]; }
    float  operator[](unsigned idx) const { return v[idx]; }

    static Vector2 fromAngle(float a)
    {
        return{ cosf(a), sinf(a) };
    }
};

// Direction Between Vectors:
    //(A-B).normal()
// Distance Between Vectors:
    //(A-B).magnitude()

inline Vector2 operator-(const Vector2  &lhs, const Vector2 &rhs)
{
    return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline Vector2 perp(const Vector2  &a)
{
    return Vector2(-a.y, a.x);
}


inline Vector2 operator+(const Vector2  &lhs, const Vector2 &rhs)
{
    return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline Vector2 operator/(const Vector2 &lhs, float rhs)
{
    return Vector2(lhs.x / rhs, lhs.y / rhs);
}
inline Vector2 operator*(const Vector2 &lhs, float rhs)
{
    return Vector2(lhs.x * rhs, lhs.y * rhs);
}
// Dot production tells us how much one vector extends
// in the direction of another vector
inline float dot(const Vector2 &lhs, const Vector2 &rhs)
{
    return lhs.x * rhs.x  +  rhs.y * lhs.y;
}

//#define EPSILON 0.0001f

inline bool operator==(const Vector2 &lhs, const Vector2 &rhs)
{
    // return lhs.x == rhs.x && lhs.y == rhs.y;
    return
    rhs.x - FLT_EPSILON < lhs.x && lhs.x < rhs.x + FLT_EPSILON &&
    rhs.y - FLT_EPSILON < lhs.y && lhs.y < rhs.y + FLT_EPSILON;

    //return fabsf(rhs.x - lhs.x) < FLT_EPSILON &&
    //       fabsf(rhs.y - lhs.y) < FLT_EPSILON;
}

inline Vector2 normal(Vector2 &a)
{
    //assert(magnitude() != 0 && "Divide by Zero");
    return a / a.magnitude();
}