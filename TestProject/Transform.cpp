#include "Transform.h"

Transform::Transform()
    :e_parent(nullptr), scale({ 1,1 }),
     position({0,0}),   angle(0) { }


Transform::~Transform()
{
    auto t = e_children;
    for each(Transform *child in t)
        child->setParent(e_parent);

    setParent(nullptr);
}

void Transform::setParent(Transform *a_parent)
{
    // If we have a parent, we need to be set free!
    if (e_parent)
        e_parent->e_children.remove(this);
        
    // If the new parent isn't null, then adopt us!
    if (a_parent)
    a_parent->e_children.push_front(this);

    // Then set the parent
    e_parent = a_parent;
}

Matrix3 Transform::getGlobalTransform() const
{   
    return
    (e_parent ? e_parent->getGlobalTransform()
              :           Matrix3::identity())
        * Matrix3::translate(position)
        * Matrix3::scale(scale)
        * Matrix3::rotate(angle);
}

void Transform::setPosition(const Vector2 &a_position)
{
    position = a_position;
}

void Transform::setScale(const Vector2 &a_scale)
{
    scale = a_scale;
}

void Transform::setAngle(float a_angle)
{
    angle = a_angle;
}

Vector2 Transform::getPosition() const
{
    return position;
}

Vector2 Transform::getScale() const
{
    return scale;
}

float Transform::getAngle() const
{
    return angle;
}
