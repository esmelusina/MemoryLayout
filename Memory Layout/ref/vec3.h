#pragma once
#include "vec2.h"
/*
Example memory layouts and data structure designs for math types.

They make heavy use of 'untagged' unions and structures to avoid
the potentially nebulous performance costs, implementation details,
and duplicity of operator overloading.

Esmeralda Salamone, esmes@aie.edu.au, 1/25/2016

For instructional use.
*/

    
__declspec(align(32)) struct vec3
{
	union
	{
        vec2 xy;
        vec2 st;
		float v[3];
		struct { float x, y, z; };
		struct { float r, g, b; };
        struct { float s, t, p; };
	};
};


vec3 normal     (const vec3 &a);

float magnitude (const vec3 &a);
float dot       (const vec3 &a, const vec3 &b);
float distance  (const vec3 &a, const vec3 &b);

vec3 cross      (const vec3 &a, const vec3 &b);

float angleBetween(const vec3 &a, const vec3 &b);

vec3 min        (const vec3 &a, const vec3 &b);
vec3 max        (const vec3 &a, const vec3 &b);
vec3 clamp      (const vec3 &a, const vec3 &min, const vec3 &max);

vec3 mix        (const vec3 &start, const vec3 &end, float t);
vec3 lerp       (const vec3 &start, const vec3 &end, float t);


vec3 reflect    (const vec3 &incident, const vec3 &normal);
vec3 project    (const vec3 &a, const vec3 &b);

vec3 operator-(const vec3 &a);

vec3 operator+(const vec3 &a, const vec3 &b);
vec3 operator-(const vec3 &a, const vec3 &b);
vec3 operator/(const vec3 &a, float b);
vec3 operator*(const vec3 &a, float b);

vec3 &operator+=(vec3 &a, const vec3 &b);
vec3 &operator-=(vec3 &a, const vec3 &b);
vec3 &operator/=(vec3 &a, float b);
vec3 &operator*=(vec3 &a, float b);


bool operator> (const vec3 &a, const vec3 &b);
bool operator>=(const vec3 &a, const vec3 &b);
bool operator< (const vec3 &a, const vec3 &b);
bool operator<=(const vec3 &a, const vec3 &b);

bool operator==(const vec3 &a, const vec3 &b);
bool operator!=(const vec3 &a, const vec3 &b);