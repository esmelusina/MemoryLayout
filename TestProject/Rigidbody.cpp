#include "Rigidbody.h"
#include "Transform.h"

Rigidbody::Rigidbody() :
    acceleration({0,0}), velocity({0,0}), mass(1),
    force({ 0,0 }), drag(0), angularAcceleration(0), angularDrag(0),angularJerk(0),angularVelocity(0)
{
}

void Rigidbody::addForce(const Vector2 &a) { force = force + a; }

void Rigidbody::addTorque(float a) { torque += a; }

void Rigidbody::integrate(Transform *t, float dt)
{

    jerk         = force / mass - acceleration; // Jerk is optional!
    acceleration = acceleration + jerk * dt; // acceleration = force/mass;
    velocity     = velocity + acceleration * dt;    
    t->setPosition(t->getPosition() + velocity * dt);

    velocity = velocity - velocity * drag * dt;
    force = { 0, 0 };

    angularJerk = torque / mass - angularAcceleration; 
    angularAcceleration = angularAcceleration + angularJerk * dt;
    angularVelocity = angularVelocity + angularAcceleration * dt;
    t->setAngle(t->getRight().angle() + angularVelocity * dt);

    angularVelocity = angularVelocity - angularVelocity * angularDrag * dt;    
    torque = 0;
}