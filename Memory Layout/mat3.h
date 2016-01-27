#pragma once
#include "vec3.h"

/*
Example memory layouts and data structure designs for math types.

They make heavy use of 'untagged' unions and structures to avoid
the potentially nebulous performance costs, implementation details,
and duplicity of operator overloading.

Esmeralda Salamone, esmes@aie.edu.au, 1/25/2016

For instructional use.
*/


__declspec(align(32)) struct mat3
{
    union
    {
        vec3  c[3];
        float m[9];
        float mm[3][3];
        struct
        {
            union { vec3 c1; vec2 right; };
            union { vec3 c2; vec2 up; };
            union { vec3 c3; vec2 position; };
        };
    };

    static constexpr mat3 identity();
};

mat3 operator+(const mat3 &a, const mat3 &b);
mat3 operator-(const mat3 &a, const mat3 &b);
mat3 operator*(const mat3 &a, const mat3 &b);   //matrix
vec3 operator*(const mat3 &a, const vec3 &b);   //vector
mat3 operator*(const mat3 &a, float b);         //scalar

mat3 &operator+=(mat3 &a, const mat3 &b);
mat3 &operator-=(mat3 &a, const mat3 &b);
mat3 &operator*=(mat3 &a, const mat3 &b);
mat3 &operator*=(mat3 &a, float b);

bool operator==(const mat3 &a, const mat3 &b);
bool operator!=(const mat3 &a, const mat3 &b);

mat3 transpose  (const mat3 &a);

//http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html
mat3 inverse    (const mat3 &a);

float determinant(const mat3 &a);

mat3 rotate     (float a);
mat3 translate  (const vec2 &xy);
mat3 scale      (const vec2 &xy);