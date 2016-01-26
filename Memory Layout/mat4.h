#pragma once
#include "vec4.h"

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
};