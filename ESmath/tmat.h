#pragma once

#include "tvec.h"

template<unsigned C, unsigned R>
struct tmat
{
    static constexpr unsigned size() { return C*R; }
    static constexpr unsigned rows() { return R; }
    static constexpr unsigned cols() { return C; }

        union
        {
            tvec<R> c[C]; // default cons should 0 us out
            float m[C*R];
            float mm[C][R];        
        };

        tvec<R> &operator[](unsigned idx)       { return c[idx]; }
        tvec<R>  operator[](unsigned idx) const { return c[idx]; }

        template<typename MATS = std::enable_if<R == C, tmat>::type>        
        static constexpr MATS identity()
        {
            MATS r;
            for (int i = 0; i < R && i < C; ++i)
                r[i][i] = 1;
            return r;
        }

        tmat() {}
        tmat(std::initializer_list<float> d) : tmat()
        {
            auto it = d.begin();
            for (unsigned i = 0; i < R*C && it != d.end(); ++i, it++) m[i] = *it;
        } 

        tmat<R, C> transpose() const
        {
            tmat<R, C> r;
            for (unsigned i = 0; i < C; ++i)
                for (unsigned j = 0; j < R; ++j)
                    r[j][i] = c[j][i];
            return r;
        }

        private:
            float r_det(int n);
        public:
            


            template<typename MATS = std::enable_if<R1 == C2, tmat<C2, R1>>::type>
            float determinant() const { return r_det(R); }

            //template<typename MATS = std::enable_if<R1 == C2, tmat<C2, R1>>::type>
            //MATS inverse() const
            //{
            //    //TODO!
            //}

            template<unsigned C1, unsigned R1, typename MATT = std::enable_if<(R1 < R && C1 < C), tmat<C1, R1>>::type>
            MATT sub(unsigned cpos, unsigned rpos)
            {
                MATT r;
                for (int i = 0; i < C1; ++i)
                    for (int j = 0; j < R1; ++j)
                        r[i][j] = mm[i][j];

                return r;
            }


            tmat inverse() const
            {

            }
};

template<unsigned C, unsigned R>
inline tmat<C, R> operator+(const tmat<C, R> &A, const  tmat<C, R> &B)
{
    tmat<R,C> r;
    for (unsigned i = 0; i < C; ++i) r[i] = A[i] + B[i];
    return r;
}

template<unsigned C, unsigned R>
inline tmat<C, R> operator-(const tmat<C, R> &A, const  tmat<C, R> &B)
{
    tmat<R, C> r;
    for (unsigned i = 0; i < C; ++i) r[i] = A[i] - B[i];
    return r;
}

template<unsigned C1, unsigned R1, unsigned C2, unsigned R2, typename MATS = std::enable_if<R1 == C2, tmat<C2,R1>>::type>
inline MATS operator*(const tmat<C1, R1> &_A, const  tmat<C2, R2> &B)
{
    MATS r;
    tmat<R1, C1> A = _A.transpose();

    for (unsigned i = 0; i < A.cols(); ++i)
        for (unsigned j = 0; j < A.cols(); ++j)
            r[i][j] = dot<R1>(A[i], B[j]);


    return r;
}


template<unsigned R, unsigned C>
float tmat<R,C>::r_det(int n)
{
    float **a = mm;
    int i, j, j1, j2;
    float det = 0;
    tmat<R,C> T;
    float **m = T.mm;

    if (n < 1) { /* Error */

    }
    else if (n == 1) { /* Shouldn't get used */
        det = a[0][0];
    }
    else if (n == 2) {
        det = a[0][0] * a[1][1] - a[1][0] * a[0][1];
    }
    else {
        det = 0;
        for (j1 = 0; j1<n; j1++) {
            for (i = 0; i<n - 1; i++)
                for (i = 1; i<n; i++) {
                    j2 = 0;
                    for (j = 0; j<n; j++) {
                        if (j == j1)
                            continue;
                        m[i - 1][j2] = a[i][j];
                        j2++;
                    }
                }
            det += pow(-1.0, 1.0 + j1 + 1.0) * a[0][j1] * Determinant(m, n - 1);
        }
    }
    return(det);
}




//    tmat transpose() const
//    {
//        tmat r;
//
//        for (unsigned i = 0; i < SIZE; ++i)
//            for (unsigned j = 0; j < SIZE; ++j)
//                r[j][i] = c[j][i];
//
//        return r;
//    }
//
//    static tmat rotate(const tvec &axis, float angle);
//    static tmat scale(const tvec &dims);
//    static tmat translate(const tvec &trans);
//private:
//    float r_det(int n);
//public:
//    float determinant() const { return r_det(SIZE); }
//
// /*   template<typename VEC2 = std::enable_if<SIZE == 1, tvec>::type> tmat inverse();
//    template<typename VEC2 = std::enable_if<SIZE == 2, tvec>::type> tmat inverse();
//    template<typename VEC2 = std::enable_if<SIZE == 3, tvec>::type> tmat inverse();
//    template<typename VEC2 = std::enable_if<SIZE == 4, tvec>::type> tmat inverse();*/
//    
//    template<unsigned C, unsigned R, unsigned SUB_SIZE, typename MATT = std::enable_if<SUB_SIZE <= SIZE && C <= SIZE-SUB_SIZE && R <= SIZE-SUB_SIZE, tmat<SUB_SIZE>>::type> MATT sub()
//    {        
//        MATT r;
//        
//        for (int c = C; c < SUB_SIZE; ++c)
//            for (int r = R; r < SUB_SIZE; ++r)
//                r[c][r] = mm[c][r];
//
//        return r;
//    }
//
//
//    tmat inverse()
//    {
//        constexpr unsigned dim = SIZE / 2 + SIZE % 2;
//        constexpr unsigned off = SIZE / 2 - SIZE % 2;
//
//        auto A = sub<  0,   0, dim>();
//        auto B = sub<off,   0, off>();
//        auto C = sub<  0, off, dim>();
//        auto D = sub<off, off, off>();    
//    }
//};
//
//template<unsigned SIZE>
//inline tmat<SIZE> operator*(const tmat<SIZE> &a_L, const tmat<SIZE> &R)
//{
//    tmat<SIZE> r, L = a_L.transpose();
//    
//    for (int i = 0; i < SIZE; ++i)
//        for (int j = 0; j < SIZE; ++j)
//            r[i][j] = dot(L[i], R[j]);
//
//    return r;
//}
//
//template<unsigned SIZE>
//inline tvec<SIZE> operator*(const tmat<SIZE> &a_L, const tvec<SIZE> &R)
//{
//    tmat<SIZE> L = a_L.transpose();
//    tvec<SIZE> r;
//
//    for (int i = 0; i < SIZE; ++i)
//            r[i] = dot(L[i], R[i]);
//
//    return r;
//}
//
//template<unsigned SIZE>
//inline bool operator==(const tmat<SIZE> &a, const tmat<SIZE> &b)
//{
//    bool r = true;
//    for (unsigned i = 0; i < SIZE; ++i) 
//        r = r && a.c[0] == b.c[0];
//    
//    return r;
//}
//template<unsigned SIZE>
//
//inline bool operator!=(const tmat<SIZE> &a, const tmat<SIZE> &b) { return !(a == b); }
//
//
//
//
//
//template<unsigned SIZE>
//float tmat<SIZE>::r_det(int n) // http://www.dkerr.com/Determinant%20of%20an%20arbitrary%20square%20matrix.htm
//{
//    float **a = mm;
//    int i, j, j1, j2;
//    float det = 0;
//    tmat T;
//    float **m = T.mm;
//
//    if (n < 1) { /* Error */
//
//    }
//    else if (n == 1) { /* Shouldn't get used */
//        det = a[0][0];
//    }
//    else if (n == 2) {
//        det = a[0][0] * a[1][1] - a[1][0] * a[0][1];
//    }
//    else {
//        det = 0;
//        for (j1 = 0; j1<n; j1++) {
//            for (i = 0; i<n - 1; i++)
//                for (i = 1; i<n; i++) {
//                    j2 = 0;
//                    for (j = 0; j<n; j++) {
//                        if (j == j1)
//                            continue;
//                        m[i - 1][j2] = a[i][j];
//                        j2++;
//                    }
//                }
//            det += pow(-1.0, 1.0 + j1 + 1.0) * a[0][j1] * Determinant(m, n - 1);
//        }
//    }
//    return(det);
//}