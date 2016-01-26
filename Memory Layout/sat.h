#pragma once
#include <vector>
#include "vec2.h"
#include "mat3.h"

struct CollisionData
{
    float PenetrationDepth; // Distance
    vec2  CollisionNormal;  // Direction
};

struct ConvexHull
{
    std::vector<vec2> verts;
};

ConvexHull   operator*(const mat3 &m, const ConvexHull &a);

CollisionData iTest_SAT(const ConvexHull &A, const ConvexHull &B);