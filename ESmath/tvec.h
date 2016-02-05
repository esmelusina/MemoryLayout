#pragma once
#include <cmath>
#include <initializer_list>

#define EPSILON 0.0001f

template<bool> struct X {};
template<> struct X<true> { float &x; X(float &a) : x(a) {} };
template<bool> struct Y {};
template<> struct Y<true> { float &y; Y(float &a) : y(a) {} };
template<bool> struct Z {};
template<> struct Z<true> { float &z; Z(float &a) : z(a) {} };
template<bool> struct W {};
template<> struct W<true> { float &w; W(float &a) : w(a) {} };

template<unsigned SIZE> struct tvec : X<SIZE >= 1>, Y<SIZE >= 2>, Z<SIZE >= 3>, W<SIZE >= 4>
{
public:
    float m_data[SIZE];

    template<bool B = SIZE == 1, typename std::enable_if<B, int>::type = 0>
    tvec(float x = 0)  : X<B>(m_data[0])
    {
        m_data[0] = x;
    }

    template<bool B = SIZE == 2, typename std::enable_if<B, int>::type = 0>
    tvec(float x = 0, float y = 0) : X<B>(m_data[0]), Y<B>(m_data[1])
    {
        m_data[0] = x;
        m_data[1] = y;
    }

    template<bool B = SIZE == 3, typename std::enable_if<B, int>::type = 0>
    tvec(float x = 0, float y = 0, float z = 0) : X<B>(m_data[0]), Y<B>(m_data[1]), Z<B>(m_data[2])
    {
        m_data[0] = x;
        m_data[1] = y;
        m_data[2] = z;
    }

    template<bool B = SIZE >= 4, typename std::enable_if<B, int>::type = 0>
    tvec(float x = 0, float y = 0, float z = 0, float w = 0) : X<B>(m_data[0]), Y<B>(m_data[1]), Z<B>(m_data[2]), W<B>(m_data[3])
    {
        m_data[0] = x;
        m_data[1] = y;
        m_data[2] = z;
        m_data[2] = w;
    }


    template<unsigned O_SIZE>
    tvec(const tvec<O_SIZE> &d) : tvec()
    {
        for (int i = 0; i < O_SIZE && i < SIZE; ++i)
            m_data[i] = d[i];
    }

    tvec(std::initializer_list<float> d) : tvec()
    {
        auto it = d.begin();
        for (unsigned i = 0; i < SIZE && it != d.end(); ++i, it++)
            m_data[i] = *it;
    }
 
    float &operator[](unsigned idx)       { return m_data[idx]; }
    float  operator[](unsigned idx) const { return m_data[idx]; }

    tvec &operator=(const tvec &a)
    {
        for (int i = 0; i < SIZE; ++i)
            m_data[i] = a[i];
        return *this;
    }
    tvec &operator-=(const tvec &a)
    {
        for (unsigned i = 0; i < SIZE; ++i)
            m_data[i] = m_data[i] - a[i];
        return *this;
    }
    tvec &operator+=(const tvec &a)
    {
        for (unsigned i = 0; i < SIZE; ++i)
            m_data[i] = m_data[i] + a[i];
        return *this;
    }
    tvec &operator/=(float s)
    {
        for (unsigned i = 0; i < SIZE; ++i)
            m_data[i] = m_data[i] / s;
        return *this;
    }
    tvec &operator*=(float s)
    {
        for (unsigned i = 0; i < SIZE; ++i)
            m_data[i] = m_data[i] * s;
        return *this;
    }

    tvec operator-() const 
    {
        tvec r = *this; r *= -1; return r;
    }
    float magnitude() const
    {
        float d = 0;
        for (int i = 0; i < SIZE; ++i)
            d += m_data[i] * m_data[i];
        return sqrtf(d);
    }
    tvec normal()    const
    {
        tvec r = *this;
        r /= magnitude();
        return r;
    }
    
    static constexpr unsigned size() { return SIZE; }
    explicit operator float*()       { return m_data; }    

    template<unsigned SUB_SIZE, unsigned OFFSET = 0, typename VECT = std::enable_if<SUB_SIZE <= SIZE, tvec<SUB_SIZE>>::type> VECT &sub()
    {
        return *((tvec<SUB_SIZE>*) m_data[OFFSET];
    }

    template<unsigned SUB_SIZE, unsigned OFFSET = 0, typename VECT = std::enable_if<SUB_SIZE <= SIZE, tvec<SUB_SIZE>>::type> VECT sub() const
    {
        return *((tvec<SUB_SIZE>*) m_data[OFFSET];
    }

    template<unsigned SUB_SIZE>
    explicit operator tvec<SUB_SIZE>&()
    {
        return sub<SUB_SIZE>();
    }

    template<typename VEC2 = std::enable_if<SIZE == 2, tvec>::type> VEC2 perp() const
    {
        return {-m_data[1], m_data[0]};
    }
    template<typename VEC2 = std::enable_if<SIZE == 2, float>::type> VEC2 angle() const
    {
        return atan2f(m_data[1], m_data[0]);
    }
};

template<unsigned SIZE> float dot(const tvec<SIZE> &a, const tvec<SIZE> &b)
{
    float t = 0;
    for (unsigned i = 0; i < SIZE; ++i)
        t += a[i] * b[i];
    return t;
}

template<unsigned SIZE> tvec<SIZE> operator/(tvec<SIZE> a, float s)             { return a /= s; }
template<unsigned SIZE> tvec<SIZE> operator*(tvec<SIZE> a, float s)             { return a *= s; }
template<unsigned SIZE> tvec<SIZE> operator*(float s, tvec<SIZE> a)             { return a *= s; }
template<unsigned SIZE> tvec<SIZE> operator-(tvec<SIZE> a, const tvec<SIZE> &b) { return a -= b; }
template<unsigned SIZE> tvec<SIZE> operator+(tvec<SIZE> a, const tvec<SIZE> &b) { return a += b; }

template<unsigned SIZE> bool operator==(const tvec<SIZE> &a, const tvec<SIZE> &b)
{
    bool r = true;
    for (unsigned i = 0; i < SIZE; ++i)
        r = r && b.m_data[i] -EPSILON < a.m_data[i] && a.m_data[i] < b.m_data[i] + EPSILON;
    return r;
}
template<unsigned SIZE> bool operator!=(const tvec<SIZE> &a, const tvec<SIZE> &b)
{
    return !(a == b);
}

template<unsigned SIZE> float distance(const tvec<SIZE> &a, const tvec<SIZE> &b) { return sqrtf(dot(a - b, a - b)); }

template<unsigned SIZE> tvec<SIZE> min(tvec<SIZE> a, const tvec<SIZE> &b)
{
    for (int i = 0; i < SIZE; ++i) a[i] = fminf(a, b);
    return a;
}
template<unsigned SIZE> tvec<SIZE> max(const tvec<SIZE> &a, const tvec<SIZE> &b)
{
    for (int i = 0; i < SIZE; ++i) a[i] = fmaxf(a, b);
    return a;
}
template<unsigned SIZE> tvec<SIZE> clamp(const tvec<SIZE> &a, const tvec<SIZE> &a_min, const tvec<SIZE> &a_max)
{
    return max(min(a_max, a), a_min);
}

template<unsigned SIZE> tvec<SIZE> lerp(const tvec<SIZE> &start, const tvec<SIZE> &end, float alpha)
{
    (1 - alpha)*start + (alpha)*end;
}

template<unsigned SIZE> tvec<SIZE> reflect(const tvec<SIZE> &incident, const tvec<SIZE> &normal)
{
    incident - 2 * dot(incident, normal)*normal;
}
template<unsigned SIZE> tvec<SIZE> project(const tvec<SIZE> &incident, const tvec<SIZE> &normal)
{
    return dot(incident, normal) * normal.normal();
}

inline tvec<3> cross(const tvec<3> &a, const tvec<3> &b)
{
    return    { a[1] * b[2] - a[2] * b[1],
                a[2] * b[0] - a[0] * b[2],
                a[0] * b[1] - a[1] * b[0] };
}