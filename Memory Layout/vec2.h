#pragma once

__declspec(align(32)) struct vec2
{
    union
    {
        float v[2];
        struct { float x, y; };
        struct { float s, t; };
    };
};

vec2 normal     (const vec2 &a);
vec2 perp       (const vec2 &a);

float magnitude (const vec2 &a);
float dot       (const vec2 &a, const vec2 &b);
float angle     (const vec2 &a);
float distance  (const vec2 &a, const vec2 &b);

vec2 min        (const vec2 &a, const vec2 &b);
vec2 max        (const vec2 &a, const vec2 &b);
vec2 clamp      (const vec2 &a, const vec2 &min, const vec2 &max);

vec2 mix        (const vec2 &start, const vec2 &end, float t);
vec2 lerp       (const vec2 &start, const vec2 &end, float t);

vec2 reflect    (const vec2 &incident, const vec2 &normal);
vec2 project    (const vec2 &a, const vec2 &b);

vec2 operator-(const vec2 &a);

vec2 operator+(const vec2 &a, const vec2 &b);
vec2 operator-(const vec2 &a, const vec2 &b);
vec2 operator/(const vec2 &a, float b);
vec2 operator*(const vec2 &a, float b);

vec2 &operator+=(vec2 &a, const vec2 &b);
vec2 &operator-=(vec2 &a, const vec2 &b);
vec2 &operator/=(vec2 &a, float b);
vec2 &operator*=(vec2 &a, float b);


bool operator> (const vec2 &a, const vec2 &b);
bool operator>=(const vec2 &a, const vec2 &b);
bool operator< (const vec2 &a, const vec2 &b);
bool operator<=(const vec2 &a, const vec2 &b);

bool operator==(const vec2 &a, const vec2 &b);
bool operator!=(const vec2 &a, const vec2 &b);