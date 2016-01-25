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


__declspec(align(32)) struct vec4
{
	union
	{
		float v[4];
		struct { vec3 xyz; float w; };
		struct { float x, y, z; };
		struct { float r, g, b, a; };
	};
};