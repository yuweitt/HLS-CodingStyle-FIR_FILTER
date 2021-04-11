#ifndef __DEC2_2STAGE_H__
#define __DEC2_2STAGE_H__
#include "dec2_alg.h"

typedef ap_fixed<8,1>   fixIn_t;
typedef ap_fixed<18,4>  fixMid_t;
typedef ap_fixed<28,7>  fixOut_t;
typedef ap_uint<1> uint1_t;
typedef ap_uint<2> uint2_t;

void dec2_2stage(fixIn_t &x,
                fixIn_t h[NUM_TAPS],
                fixOut_t &y);

#endif
