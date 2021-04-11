#ifndef __DEC2_MULTI_BLOCK_H__
#define __DEC2_MULTI_BLOCK_H__
#include <ap_fixed.h>
#include <hls_stream.h>

#define S_RATE	    		2
#define T_RATE              S_RATE * S_RATE
#define NUM_TAPS            4

typedef ap_fixed<8,1> fixIn_t;
typedef ap_fixed<18,4> fixMid_t;
typedef ap_fixed<28,7> fixOut_t;
typedef hls::stream<fixIn_t> streamIn_t;
typedef hls::stream<fixMid_t> streamMid_t;
typedef hls::stream<fixOut_t> streamOut_t;

void dec2_2stage(streamIn_t &x,
                fixIn_t h[NUM_TAPS],
                streamOut_t &y);

#endif
