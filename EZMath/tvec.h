#pragma once
#include <initializer_list>
#include <type_traits>

/*
    vec.swizzle<1,2,3,1,2,3>();


*/

template<unsigned N, typename T = float>
struct tvec
{
    template<unsigned i, unsigned ...iargs>
    tvec<sizeof...(iargs)> swizzle() const;
};


template<unsigned N, typename T>
template<unsigned i, unsigned ...iargs>
inline tvec<sizeof...(iargs)> tvec<N, T>::swizzle() const
{
    return tvec<sizeof...(iargs)>();
}



//template<unsigned N, typename T = float>
//struct tvec
//{
//    T*  p_data[N]; 
//    T   m_data[N];
//
//    template<unsigned S>
//    tvec<S + N> concat(const tvec<S> &a) const;
//
//    template<unsigned S, unsigned I, unsigned...i_args>
//    tvec<S> swizzle() const;
//};
//
//
//template<unsigned N, typename T>
//template<unsigned S, unsigned I, unsigned ...i_args>
//inline tvec<S> tvec<N, T>::swizzle() const
//{
//    tvec<1, T> ret;
//
//    ret.m_data[0] = m_data[I];
//    ret.concat(swizzle<S,i_args...>());
//}

