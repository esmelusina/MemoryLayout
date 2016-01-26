#pragma once

struct aabb;
struct circle;
struct ray;
struct plane;
struct vec2;
struct mat3;

// Useful, but not necessary yet!
aabb   operator*(const mat3 &m, const aabb   &a);
circle operator*(const mat3 &m, const circle &a);
ray    operator*(const mat3 &m, const ray    &a);
plane  operator*(const mat3 &m, const plane  &a);

float point_plane_dist (const vec2 &a,  const plane &b);
float ray_plane_dist   (const ray  &a,  const plane &b);

// Should also have way to access a min and max
vec2 min   (const vec2 &a, const vec2 &b);
vec2 max   (const vec2 &a, const vec2 &b);
vec2 clamp (const vec2 &a, const vec2 &min, const vec2 &max);

// determine whether or not the shapes are overlapping... fast!
bool iTest_aabb				(const aabb   &a, const aabb	&b);
bool iTest_aabb_circle		(const aabb   &a, const circle	&b);
bool iTest_aabb_plane		(const aabb   &a, const plane	&b);
bool iTest_aabb_ray			(const aabb   &a, const ray		&b);
bool iTest_circle      	    (const circle &a, const circle	&b);
bool iTest_circle_plane		(const circle &a, const plane	&b);
bool iTest_circle_ray		(const circle &a, const ray		&b);
bool iTest_ray_plane		(const ray    &a, const plane	&b);

// Calculate the Minimum Translation Vector
vec2 mtv_aabb				(const aabb   &a, const aabb	&b);
vec2 mtv_aabb_circle		(const aabb   &a, const circle	&b);
vec2 mtv_aabb_plane			(const aabb   &a, const plane	&b);
vec2 mtv_aabb_ray			(const aabb   &a, const ray		&b);
vec2 mtv_circle      		(const circle &a, const circle	&b);
vec2 mtv_circle_plane		(const circle &a, const plane	&b);
vec2 mtv_circle_ray			(const circle &a, const ray		&b);
vec2 mtv_ray_plane			(const ray    &a, const plane	&b);

struct vec2 { float x, y; };

struct ray
{
	vec2  p, // Position
		  d; // Direction
	float l; // length (possibly infinite?) Just use a big value...
};
struct plane
{
	vec2 p, // Position
		 n; // Normal
};

struct circle
{
	vec2  p;  // position
	float r; // radius
};

struct aabb
{
	vec2 p, e; // position and half-extents
	vec2 min() const; // p - e
	vec2 max() const; // p + e
};