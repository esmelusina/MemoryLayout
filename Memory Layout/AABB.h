#pragma once
#include <cmath>
#include <cfloat>

struct vec2 { float x, y; };

struct AABB
{
	vec2 m_pos, m_dim;		//		: vec2 m_min, m_max;
	vec2 min(); // m_pos-m_dim/2	: m_min
	vec2 max(); // m_pos+m_dim/2	: m_max
	vec2 pos(); // m_pos			: (m_min+m_max)/2
	vec2 dim(); // m_dim			: m_max - m_min
};
//smallest/largest of the x and y separately

// a < b? a : b
vec2 min(vec2 *v, size_t n)
{
	vec2 m = {FLT_MAX, FLT_MAX};
	for (int i = 0; i < n; ++i)
		m = { fminf(m.x, v[i].x),
			  fminf(m.y, v[i].y) };
	return m;
}

vec2 max(vec2 *v, size_t n)
{
	vec2 m = { FLT_MIN, FLT_MIN };
	for (int i = 0; i < n; ++i)
		m = { fmaxf(m.x, v[i].x),
			  fmaxf(m.y, v[i].y) };
	return m;

	
}

AABB genAABB(vec2 *pts, size_t n)
{
	vec2 m = min(pts, n);
	vec2 M = max(pts, n);

	vec2 p = {(M.x + m.x)/2, (M.y + m.y)/2};
	vec2 d = { M.x - m.x,     M.y + m.y};

	return{ p,d };
}
// w = h*sin(a) + w*cos(a);
// h = w*sin(a) + h*cos(a);
AABB rotate(const AABB &aabb, float a)
{
	float w = aabb.m_dim.x;
	float h = aabb.m_dim.y;

	float wp = fabs(h*sinf(a)) + fabs(w*cosf(a));
	float hp = fabs(w*sinf(a)) + fabs(h*cosf(a));

	return { aabb.m_pos,{ wp,hp } };
}