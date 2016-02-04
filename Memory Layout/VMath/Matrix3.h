#pragma once
#include "Vector3.h"
#include "Vector2.h"

struct Matrix3
{
    Matrix3() {}
    union
    {
        float   v[9];
        float   m[3][3];
        Vector3 c[3];
    };

    Matrix3 transpose() const
    {
        Matrix3 r;
        r.c[0] = Vector3(m[0][0], m[1][0], m[2][0]);
        r.c[1] = Vector3(m[0][1], m[1][1], m[2][1]);
        r.c[2] = Vector3(m[0][2], m[1][2], m[2][2]);
        return r;
    }
    
    static Matrix3 identity()
    {
        Matrix3 r;
        r.c[0] = Vector3(1,0,0);
        r.c[1] = Vector3(0,1,0);
        r.c[2] = Vector3(0,0,1);
        return r;
    }

    // angle, in degrees
    static Matrix3 rotate(float angle)
    {
        Matrix3 r = identity();
        r.c[0] = Vector3( cosf(angle), sinf(angle), 0);
        r.c[1] = Vector3( -sinf(angle), cosf(angle), 0);
        return r;
    }

    static Matrix3 scale(const Vector2 &xy)
    {
        Matrix3 r = identity();
        r.m[0][0] = xy.x;
        r.m[1][1] = xy.y;
        return r;
    }

    static Matrix3 translate(const Vector2 &xy)
    {
        Matrix3 r = identity();
        r.m[2][0] = xy.x;
        r.m[2][1] = xy.y;
        return r;
    }

    //Matrix3 &operator*=(const Matrix3 &rhs);
};

Vector3 operator*(const Matrix3 &_A, const Vector3 &b);
Matrix3 operator*(const Matrix3 &_A, const Matrix3 &B);