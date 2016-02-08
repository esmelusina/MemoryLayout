#pragma once
#include "VMath.h"

class Rigidbody
{
public:
    Vector2 velocity, acceleration, force, jerk;
    float mass, drag;

    float angularVelocity, angularAcceleration, torque;
    float angularDrag;

    Rigidbody();
    void addForce(const Vector2 &);
    void addTorque(float);

    void integrate(class Transform *, float dt);
};