#pragma once
#include <array>


template<unsigned S, typename T, bool>
class rvec
{
    std::array<T, S> data;
public:
    T &operator[] (unsigned idx)       { return data[idx]; }
    T  operator[] (unsigned idx) const { return data[idx]; }
};



template<unsigned S, typename T>
class rvec<S,T,true>
{
    std::array<T*, S> data;
public:
    T &operator[] (unsigned idx)       { return *data[idx]; }
    T  operator[] (unsigned idx) const { return *data[idx]; }
};



template<unsigned S, typename T = float, bool REF = false>
class tvec : rvec<S,T,REF>
{
    tvec<S, T,  true> swizzle();
    tvec<S, T, false> swizzle() const;
};