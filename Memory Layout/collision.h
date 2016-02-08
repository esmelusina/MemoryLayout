#pragma once
#include "Shapes.h"
#include "VMath.h"

struct CollisionData // Wrapper for Minimum Translation Vector
{
    bool     collides;         
    float    PenetrationDepth; 
    Vector2  CollisionNormal;
    Vector2  PointOfContact;
};

// Some distance formula
float point_plane_dist  (const Vector2 &a, const Plane &b);
float ray_plane_dist    (const Ray     &a, const Plane &b);

CollisionData iTest(const AABB   &a, const AABB   &b);
CollisionData iTest(const AABB   &a, const Circle &b);
CollisionData iTest(const AABB   &a, const Ray    &b);
CollisionData iTest(const AABB   &a, const Plane  &b);
CollisionData iTest(const Circle &b, const AABB   &a);
CollisionData iTest(const Plane  &b, const AABB   &a);
CollisionData iTest(const Ray    &b, const AABB   &a);

CollisionData iTest(const Circle &a, const Circle &b);
CollisionData iTest(const Circle &a, const Plane  &b);
CollisionData iTest(const Circle &a, const Ray    &b);
CollisionData iTest(const Plane  &b, const Circle &a);
CollisionData iTest(const Ray    &b, const Circle &a);

CollisionData iTest(const Ray    &a, const Plane  &b);
CollisionData iTest(const Plane  &b, const Ray    &a);

CollisionData iTest(const ConvexHull &A, const ConvexHull &B);
CollisionData iTest(const ConvexHull &A, const Circle     &b);
CollisionData iTest(const ConvexHull &A, const Ray        &b);
CollisionData iTest(const ConvexHull &A, const Plane      &b);
CollisionData iTest(const ConvexHull &A, const AABB       &b);
CollisionData iTest(const Circle     &b, const ConvexHull &A);
CollisionData iTest(const Ray        &b, const ConvexHull &A);
CollisionData iTest(const Plane      &b, const ConvexHull &A);
CollisionData iTest(const AABB       &b, const ConvexHull &A);