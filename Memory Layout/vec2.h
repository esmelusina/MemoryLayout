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

// a/magnitude(a)
vec2 normal     (const vec2 &a);
// <-y,x> or <y,-x> (usually first
vec2 perp       (const vec2 &a);

float magnitude (const vec2 &a);
float dot       (const vec2 &a, const vec2 &b);
// atan2f
float angle     (const vec2 &a);
float distance  (const vec2 &a, const vec2 &b);

// acosf(dot(a,b) / (magnitude(a)*magnitude(b)))
float angleBetween(const vec2 &a, const vec2 &b);

// component-wise, new vector of biggest/smallest x and y separately
vec2 abs        (const vec2 &a);
vec2 min        (const vec2 &a, const vec2 &b);
vec2 max        (const vec2 &a, const vec2 &b);
vec2 clamp      (const vec2 &a, const vec2 &min, const vec2 &max);

//start*(1-alpha) + end*(alpha)
vec2 mix        (const vec2 &start, const vec2 &end, float t);

// (end-start)*alpha + start
vec2 lerp       (const vec2 &start, const vec2 &end, float t);

// incident - 2*dot(incident,normal)*normal
vec2 reflect    (const vec2 &incident, const vec2 &normal);

// dot(a,b) * normal(b)
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

//component wise- x1 < x2 && y1 < y2
bool operator> (const vec2 &a, const vec2 &b);
bool operator>=(const vec2 &a, const vec2 &b);
bool operator< (const vec2 &a, const vec2 &b);
bool operator<=(const vec2 &a, const vec2 &b);

bool operator==(const vec2 &a, const vec2 &b);
bool operator!=(const vec2 &a, const vec2 &b);