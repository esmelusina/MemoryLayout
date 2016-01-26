
#include "sat.h"
#include <cmath>
#include <list>
#include <algorithm>

CollisionData iTest_SAT(const ConvexHull &A, const ConvexHull &B)
{
    CollisionData cd = { INFINITY };

    std::vector<vec2> axes;
    std::vector<float> pdepth;
    axes.reserve(A.verts.size() + B.verts.size());
    
    // Determine all of the possible axes of separation.     
        // for each shape  
            // for each adjacent pair of vertices
                // perpendicular vector of the normal of the difference
    for (int i = 0; i < A.verts.size(); ++i)
        axes.push_back(perp(normal(A.verts[i]-A.verts[(i+1) % A.verts.size()])));

    for (int i = 0; i < B.verts.size(); ++i)
        axes.push_back(perp(normal(B.verts[i] - B.verts[(i + 1) % B.verts.size()])));


    for (int i = 0; i < axes.size(); ++i)
    {
        float amin = INFINITY, amax = -INFINITY;
        float bmin = INFINITY, bmax = -INFINITY;

        for (int i = 0; i < A.verts.size(); ++i)
        {
            float pp;
            // calculate the projected point!
            amin = fminf(pp, amin);
            amax = fminf(pp, amax);
        }

        for (int i = 0; i < A.verts.size(); ++i)
        {
            float pp;
            // calculate the projected point!
            amin = fminf(pp, amin);
            amax = fminf(pp, amax);
        }

        float pdepth = fminf(amax - bmin, bmax - amin);
        if (pdepth < cd.PenetrationDepth)
        {
            cd = { pdepth, axes[i] };
            if (pdepth < 0) return cd;
        }
    }

    
}