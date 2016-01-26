#pragma once
#include <cmath>

/*
Example memory layouts and data structure designs for math types.

They make heavy use of 'untagged' unions and structures to avoid
the potentially nebulous performance costs, implementation details,
and duplicity of operator overloading.

Esmeralda Salamone, esmes@aie.edu.au, 1/25/2016

For instructional use.
*/

template<size_t RANGE>
class tvec
{
protected:
	float m_data[RANGE];
public:
	constexpr size_t size()	   { return RANGE; }
	explicit operator float*() { return m_data; }

	float  operator[](size_t idx) const { return m_data[idx]; }
	float &operator[](size_t idx)       { return m_data[idx]; }


	float magnitude()
	{
		float t = 0;
		for (size_t i = 0; i < RANGE; ++i)
			t += m_data[i] * m_data[i];
		return sqrtf(t);
	}

	tvec operator+(tvec b)
	{
		tvec r = *this;
		r += b;
		return r;
	}

	tvec operator+=(tvec b)
	{
		for (size_t i = 0; i < RANGE; ++i)
			m_data[i] += b.m_data[i];
	}
};


// Could do stuff like this
//__declspec(align(32)) class vec3 : public tvec<3>
//{
//public:
//	vec3 cross(const vec3 &rhs);
//};