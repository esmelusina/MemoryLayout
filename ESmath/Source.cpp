
#include "tvec.h"
#include "tmat.h"
#include <cassert>

void main()
{
    tmat<3, 2> t;
    tmat<2, 4> r;

    t.sub<1, 1>(1,2);

    tmat<2,2> f = t * r;
}