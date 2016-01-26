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
		float v[3];
		struct { float x, y, z; };
		struct { float r, g, b; };
	};

	// unary and assignment operations
};

// binary operations