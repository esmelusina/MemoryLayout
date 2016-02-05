#pragma once

#include "tvec.h"


#define CRTEMP template<unsigned C, unsigned R>


CRTEMP struct tmat
{
private:
    
    union
    {
        tvec<R> c[C];
        float   m[C*R];
        float  mm[C][R];
    };

public:

    static constexpr unsigned size()   { return C*R; }
    static constexpr unsigned rows()   { return R; }
    static constexpr unsigned cols()   { return C; }


        tvec<R> &operator[](unsigned idx)       { return c[idx]; }
        tvec<R>  operator[](unsigned idx) const { return c[idx]; }

    


        tmat() {}
        tmat(std::initializer_list<float> d) : tmat()
        {
            auto it = d.begin();
            for (unsigned i = 0; i < R*C && it != d.end(); ++i, it++) m[i] = *it;
        } 

        tmat(std::initializer_list<tvec<R>> d) : tmat()
        {
            auto it = d.begin();
            for (unsigned i = 0; i < C && it != d.end(); ++i, it++) c[i] = *it;
        }

        tmat<R, C> transpose() const
        {
            tmat<R, C> r;
            for (unsigned i = 0; i < C; ++i)
                for (unsigned j = 0; j < R; ++j)
                    r[j][i] = c[j][i];
            return r;
        }

        explicit operator float*() { return m; }
            
        tmat operator-()
        {
            for (unsigned i = 0; i < R*C; ++i)
                m[i] *= -1;
        }
       
        template<unsigned C1, unsigned R1, typename MATT = std::enable_if<(R1 < R && C1 < C), tmat<C1, R1>>::type>
        MATT getBlock(unsigned cpos, unsigned rpos) const
        {
            MATT r;
            for (int i = 0; i < C1; ++i)
                for (int j = 0; j < R1; ++j)
                    r[i][j] = mm[i][j];

            return r;
        }

        template<unsigned C1, unsigned R1, typename MATT = std::enable_if<(R1 < R && C1 < C), tmat<C1, R1>>::type>
        void setBlock(const MATT &block, unsigned cpos, unsigned rpos)
            {                    
                for (unsigned i = cpos; cpos < C1; ++i)
                    for (unsigned j = rpos; rpos < R1; ++j)
                        mm[i][j] = block[i][j];
            }
            
        template<typename MATT = std::enable_if<C == R, tmat>::type> MATT inverse() const;           
        template<typename FLOAT = std::enable_if<R == C, float>::type> float determinant() const;
        
        template<typename MATS = std::enable_if<R == C, tmat>::type>
        static MATS identity()
        {
            MATS r;
            for (int i = 0; i < R && i < C; ++i)
                r[i][i] = 1;
            return r;
        }

        static tmat translate(const tvec<R-1> &v)
        {
            tmat r;
            for (unsigned j = 0; j < R; j++)
                r[C - 1][j] = v[j];
        }

        static tmat scale(const tvec<R-1> &v)
        {
            tmat r;
            for (int j = 0; j < R; j++)
                r[j][j] = v[j];
        }


        static tmat rotateO(unsigned a, unsigned b, float angle)
        {
            tmat r = identity();

            r[a][a] = r[b][b] = cosf(angle);
            r[a][b] = -sinf(angle);
            r[b][a] = -r[a][b];
            
            return r;
        }

        static tmat rotate(const tvec<R - 1> &v, float angle)
        {
            tmat r = identity();            
            tmat<R - 1, R - 1> R = tmat< R - 1, R - 1>::identity();            
            tvec<R - 1> V = v;
            unsigned n = R - 1;
            unsigned k = 1;

            for (unsigned r = 2; r < n; ++r)
                for (unsigned c = n; c >= n; --c)
                {
                    k++;
                    rotateO(c, c - 1, atan2f(V,V));
                }

            return r;
        }
};



CRTEMP inline tmat<C, R> operator+(const tmat<C, R> &A, const  tmat<C, R> &B)
{
    tmat<R, C> r;
    for (unsigned i = 0; i < C; ++i) r[i] = A[i] + B[i];
    return r;
}
CRTEMP inline tmat<C, R> operator-(const tmat<C, R> &A, const  tmat<C, R> &B)
{
    tmat<R, C> r;
    for (unsigned i = 0; i < C; ++i) r[i] = A[i] - B[i];
    return r;
}

template<unsigned C1, unsigned R1, unsigned C2, unsigned R2, typename MATS = std::enable_if<C1 == R2, tmat<C2, R1>>::type>
inline tmat<C2, R1> operator*(const tmat<C1, R1> &_A, const  tmat<C2, R2> &B)
{
    tmat<C2, R1> r;
    tmat<R1, C1> A = _A.transpose();

    for (unsigned i = 0; i < A.cols(); ++i)
        for (unsigned j = 0; j < A.cols(); ++j)
            r[i][j] = dot<R1>(A[i], B[j]);

    return r;
}

CRTEMP inline tmat<C, R> operator*(const tmat<C, R> &A, float scalar)
{
    tmat<C, R> r;
    for (unsigned i = 0; i < C; ++i)
        for (unsigned j = 0; j < R; ++j)
            r[i][j] = A[i][j] * scalar;
    return r;
}
CRTEMP inline tmat<C, R> operator*(float scalar, const tmat<C, R> &A)
{
    return A*scalar;
}
CRTEMP inline tvec<R>    operator*(const tmat<C, R> &A, const tvec<R> &v)
{
    tmat<R, 1> B = {v};
    return A*B;
}


template<> template<> float tmat<1, 1>::determinant() const { return mm[0][0]; }
template<> template<> float tmat<2, 2>::determinant() const { return mm[0][0] * mm[1][1] - mm[1][0] * mm[0][1]; }

CRTEMP template<typename FLOAT> float tmat<C,R>::determinant() const
{
    static_assert(C == R, "Only usable by square matrices.");
    constexpr unsigned n = C;
    constexpr unsigned size = C - 1;

    unsigned i, j, j1, j2;
    float det = 0;
    tmat<size, size> M;

    for (j1 = 0; j1 < n; ++j1)
    {
        for (i = 1; i < n; ++i)
        {
            j2 = 0;
            for (j = 0; j < n; j++)
            {
                if (j == j1) continue;
                M[i - 1][j2] = mm[i][j];
            }
        }
    det += powf(-1.f, 2.f + j1) * mm[0][j1] * M.determinant();
    }
    return det;
}


template<> template<> tmat<1, 1> tmat<1, 1 >::inverse() const { return *this; }
template<> template<> tmat<2, 2> tmat<2, 2 >::inverse() const { tmat r = { m[3], -m[2] - m[1], m[0] }; return r * (1 / determinant()); }
template<> template<> tmat<3, 3> tmat<3, 3 >::inverse() const
{
    float a = m[0];
    float d = m[1];
    float g = m[2];
    float b = m[3];
    float e = m[4];
    float h = m[5];
    float c = m[6];
    float f = m[7];
    float i = m[8];

    float A = e*i - f*h;
    float B = -d*i + f*g;
    float C = d*h - e*g;
    float D = -b*i + c*h;
    float E = a*i - c*g;
    float F = -a*h + b*g;
    float G = b*f - c*e;
    float H = -a*f + c*d;
    float I = a*e - b*d;

    tmat r = { A,B,C,D,E,F,G,H,I };

    return r * (1 / determinant());
}

CRTEMP template<typename MATT = std::enable_if<C == R, tmat>::type> MATT tmat<C,R>::inverse() const
{
    tmat<C, R> r;
    constexpr unsigned d1 = C / 2 + C % 2;
    constexpr unsigned d2 = C / 2;

    tmat<d1, d1> A = getBlock<d1, d1>(0, 0);
    tmat<d2, d1> B = getBlock<d2, d1>(d1, 0);
    tmat<d1, d2> C = getBlock<d1, d2>(0, d1);
    tmat<d2, d2> D = getBlock<d2, d2>(d1, d1);

    tmat<d2, d1> BDI = B*D.inverse();
    tmat<d1, d2> DIC = D.inverse()*C;
    tmat<d1, d1> AID = (A - BDI*C).inverse();

    tmat<d1, d1> tl = AID;
    tmat<d2, d1> tr = -AID * BDI;
    tmat<d1, d2> bl = -DIC * AID;
    tmat<d2, d2> br = D.inverse() + DIC*AID*BDI;

    r.setBlock<d1, d1>(tl, 0, 0);
    r.setBlock<d2, d1>(tr, d1, 0);
    r.setBlock<d1, d2>(bl, 0, d1);
    r.setBlock<d2, d2>(br, d1, d1);

    return r;
}
