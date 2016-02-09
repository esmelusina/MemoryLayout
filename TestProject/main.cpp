#include "sfwdraw.h"
#include "VMath.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "Shapes.h"

// Replace with your mat4 potentially
struct _mat4
{
    float m[16];
};

_mat4 mat3to4(float *m, float Z)
{  
    return
    {   m[0],m[1], 0, m[2],
        m[3],m[4], 0, m[5],
          0 ,  0 , 1 ,  0,
        m[6],m[7], Z, m[8] };
}

int main()
{

        Circle C = { {0,1},{2} };
        AABB j = { {0,1}, {3,4} };
        Matrix3 q = Matrix3::translate({ 1,1 }) * Matrix3::rotate(3.14159265359 / 2);// */ *Matrix3::scale({ 2,1 });
        q * C;
        q * j;






    sfw::initContext();
    int  handle = sfw::loadTextureMap("./dino.png");

    Transform transform1, transform2;
    Transform orbitalSpinner;

    Rigidbody rigidbody1;
    rigidbody1.drag = .5f;

    Matrix3 mat;

    float speed = 400;
    float angularSpeed = 40;
    float x = 400, y = 400, angle = 0;

    while (sfw::stepContext())
    {
        //if (sfw::getKey('S')) rigidbody1.addForce({ 0, -speed }); 
        if (sfw::getKey('W')) rigidbody1.addForce(transform1.getRight() * speed);
        //if (sfw::getKey('A')) rigidbody1.addForce({ -speed, 0 }); 
        //if (sfw::getKey('D')) rigidbody1.addForce({  speed, 0 }); 
        if (sfw::getKey('Q')) rigidbody1.addTorque(angularSpeed);
        if (sfw::getKey('E')) rigidbody1.addTorque(-angularSpeed);

        // Transformation hierarchy
        transform1.setAngle(angle);
        transform1.setScale({ 500,300 });

        rigidbody1.integrate(&transform1, sfw::getDeltaTime());

        orbitalSpinner.setParent(&transform1);
        orbitalSpinner.setAngle(-sfw::getTime());

        transform2.setParent   (&orbitalSpinner);
        transform2.setPosition ({ .25f, .25f });
        transform2.setScale    ({ .5f,.5f });

        auto m1 = mat3to4(transform1.getGlobalTransform().v, 0.25);
        auto m2 = mat3to4(transform2.getGlobalTransform().v, 0.1);

        // Using matrices only
        mat = Matrix3::translate({ 300, 300 })
            * Matrix3::scale({ 10, 10 })
            * Matrix3::rotate(sfw::getTime());
        auto m3 = mat3to4(mat.v, -0.5);

        sfw::drawTextureMatrix(handle, 0, WHITE,   m1.m);
        sfw::drawTextureMatrix(handle, 0, MAGENTA, m2.m);
        sfw::drawTextureMatrix(handle, 0, BLUE,    m3.m);
    }
    sfw::termContext();

    return 0;
}