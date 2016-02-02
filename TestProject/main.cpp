#include "sfwdraw.h"
#include "VMath.h"

// Replace with your mat4 potentially
struct _mat4
{
    float m[16];
};

_mat4 mat3to4(float *m)
{  
    return
    {   m[0],m[1], 0, m[2],
        m[3],m[4], 0, m[5],
          0 ,  0 , 1 ,  0,
        m[6],m[7], 0, m[8] };
}

int main()
{
    sfw::initContext();
    int  handle = sfw::loadTextureMap("./dino.png");

    float x = 400, y = 400;
    float angle = 0;
    float speed = 100;
    float angularSpeed = 15;
    while (sfw::stepContext())
    {        
        if (sfw::getKey('S')) y -= sfw::getDeltaTime()  * speed;
        if (sfw::getKey('W')) y += sfw::getDeltaTime()  * speed;
        if (sfw::getKey('A')) x -= sfw::getDeltaTime()  * speed;
        if (sfw::getKey('D')) x += sfw::getDeltaTime()  * speed;
        if (sfw::getKey('Q')) angle += sfw::getDeltaTime() * angularSpeed;
        if (sfw::getKey('E')) angle -= sfw::getDeltaTime() * angularSpeed;

        Matrix3 mat = Matrix3::translate({ x,y })
                    * Matrix3::scale(200)
                    * Matrix3::rotate(angle);

        Matrix3 mat1 =
                       Matrix3::rotate(-sfw::getTime())
                     * Matrix3::translate({ .25f, .25f })
                     * Matrix3::scale(.5f);

        sfw::drawTextureMatrix(handle, 0, WHITE, mat3to4(mat.v).m);
        sfw::drawTextureMatrix(handle, 0, MAGENTA, mat3to4((mat * mat1).v).m);
    }
    sfw::termContext();

    return 0;
}