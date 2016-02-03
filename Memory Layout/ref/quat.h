#pragma once
#include "mat3.h"

struct quat
{
    union
    {
    float x, y, z, w;
    float v[4];
    };
};

quat makeRotate(const vec3 &axis, float angle);
mat3 quatToMat3(const quat &);
quat mat3ToQuat(const mat3 &);
quat slerp(quat, quat, float);