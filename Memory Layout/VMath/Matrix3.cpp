#include "Matrix3.h"

Matrix3 operator*(const Matrix3 &_A, const Matrix3 &B)
{
    //A can now access rows as vector3
    Matrix3 r, A = _A.transpose();

    //for (size_t i = 0; i < 3; ++i)
    //    r.c[i] = Vector3(dot(A.c[0], B.c[i]), dot(A.c[1], B.c[i]), dot(A.c[2], B.c[i]));

    // Filling out columns for r here:
    r.c[0] = Vector3(dot(A.c[0], B.c[0]), dot(A.c[1], B.c[0]), dot(A.c[2], B.c[0]));
    r.c[1] = Vector3(dot(A.c[0], B.c[1]), dot(A.c[1], B.c[1]), dot(A.c[2], B.c[1]));
    r.c[2] = Vector3(dot(A.c[0], B.c[2]), dot(A.c[1], B.c[2]), dot(A.c[2], B.c[2]));

    return r;
}

Vector3 operator*(const Matrix3 &_A, const Vector3 &b)
{
    Matrix3 A = _A.transpose();
    Vector3 r;

    r.x = dot(A.c[0], b);
    r.y = dot(A.c[1], b);
    r.z = dot(A.c[2], b);

    return r;
}