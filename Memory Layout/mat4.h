#pragma once
#include "vec4.h"
#include "mat3.h"
/*
Example memory layouts and data structure designs for math types.

They make heavy use of 'untagged' unions and structures to avoid
the potentially nebulous performance costs, implementation details,
and duplicity of operator overloading.

Esmeralda Salamone, esmes@aie.edu.au, 1/25/2016

For instructional use.
*/

    
__declspec(align(32)) struct mat4
{
	union
	{
		vec4  c[4];
		float m[16];
		float mm[4][4];
		struct
		{
			union { vec4 c1; vec3 right;    };
			union { vec4 c2; vec3 up;       };
			union { vec4 c3; vec3 forward;  };
			union { vec4 c4; vec3 position; };
		};
	};
    static constexpr mat4 identity();
};

mat4 operator+(const mat4 &a, const mat4 &b);
mat4 operator-(const mat4 &a, const mat4 &b);
mat4 operator*(const mat4 &a, const mat4 &b);

mat4 &operator+=(const mat4 &a, const mat4 &b);
mat4 &operator-=(const mat4 &a, const mat4 &b);
mat4 &operator*=(const mat4 &a, const mat4 &b);

mat4 transpose(const mat4 &a);
mat4 inverse(const mat4 &a); //aka, the terror

mat4 rotate(const vec3 &axis, float angle);
mat4 scale(const vec3 &xyz);
mat4 translate(const vec3 &xyz);

mat4 ortho      (float l, float r, float t, float b, float n, float f);
mat4 frustum    (float l, float r, float t, float b, float n, float f);
mat4 perspective(float fov, float aspect, float n, float f); // assert n > 0 && f > n
mat4 lookAt     (const vec3 &eye, const vec3 &target, const vec3 &up);
