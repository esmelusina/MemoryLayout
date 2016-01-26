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
};