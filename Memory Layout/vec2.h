#pragma once

__declspec(align(32)) struct vec2
{
    union
    {
        float v[2];
        struct { float x, y; };
        struct { float u, v; };
    };
    //unary operations and assignments
};

// binary operations

vec2 operator-(const vec2 &a, const vec2 &b);
vec2 normal(const vec2 &a);
vec2 perp(const vec2 &a);