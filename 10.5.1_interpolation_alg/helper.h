#ifndef __HELPER_H__
#define __HELPER_H__
// helper structs for statically computing log2 like functions (nbits, log2_floor, log2_ceil)
//   using recursive templates
template<unsigned char N>
struct s_N {
    template<unsigned X>
    struct s_X {
        enum {
        X2 = X >> N,
        N_div_2 = N >> 1,
        nbits = X ? (X2 ? N + (int) s_N<N_div_2>::template s_X<X2>::nbits : (int) s_N<N_div_2>::template s_X<X>::nbits) : 0
        };
    };
};
template<>
struct s_N<0> {
    template<unsigned X>
    struct s_X {
        enum {nbits = !!X };
    };
};


template<unsigned X>
struct nbits {
    enum { val = X ? s_N<16>::s_X<X>::nbits : 1 };
};

template<unsigned X>
struct log2_floor {
    enum { val = nbits<X>::val - 1 };
};

// log2 of 0 is not defined: generate compiler error
template<> struct log2_floor<0> {};

template<unsigned X>
struct log2_ceil {
    enum { lf = log2_floor<X>::val, val = (X == (1 << lf) ? lf : lf+1) };
};

// log2 of 0 is not defined: generate compiler error
template<> struct log2_ceil<0> {};

#endif