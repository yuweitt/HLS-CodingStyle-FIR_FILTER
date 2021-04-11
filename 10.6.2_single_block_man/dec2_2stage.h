#ifndef __DEC2_2STAGE_H__
#define __DEC2_2STAGE_H__
#include <hls_stream.h>
#include "dec2_i2.hpp"

typedef ap_fixed<8,1> fixIn_t;
typedef ap_fixed<18,4> fixMid_t;
typedef ap_fixed<28,7> fixOut_t;
typedef hls::stream<fixIn_t> streamIn_t;
typedef hls::stream<fixMid_t> streamMid_t;
typedef hls::stream<fixOut_t> streamOut_t;

void dec2_2stage(streamIn_t* x,
                fixIn_t h[4],
                streamOut_t* y);

#endif
