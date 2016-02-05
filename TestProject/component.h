#pragma once
#include <vector>


/*
    Base object that has a static contiguous typed array.
    Construction of an object adds it to the array.
*/


template<typename T>
struct component
{
    static std::vector<T> &getData() { static std::vector<T> dat; return dat; }
    static int make() { getData().push_back(build()); }
    // new / delete are overloaded
};

struct transform : component<transform>
{
    


};

#define ALL_THE_COMPONENT_STUFF(type) struct type { 


ALL_THE_COMPONENT_STUFF(type)
};