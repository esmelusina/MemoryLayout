#pragma once
#include "VMath.h"

class Rigidbody
{
public:
    float mass;

    Vector2 velocity, acceleration, force, jerk;
    float drag;

    float angularVelocity, angularAcceleration, torque, angularJerk;
    float angularDrag;

    Rigidbody();
    void addForce(const Vector2 &);
    void addTorque(float);

    void integrate(class Transform *, float dt);
};