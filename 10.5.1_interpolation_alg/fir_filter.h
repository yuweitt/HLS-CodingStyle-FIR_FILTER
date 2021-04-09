#ifndef __FIR_FILTER_H__
#define __FIR_FILTER_H__
#include <ap_fixed.h>
#include <hls_stream.h>

#define	NUM_TAPS					4
#define S_RATE                      2

typedef ap_fixed<8,1> fixIn_t;
typedef ap_fixed<18,4> fixOut_t;
typedef hls::stream<fixIn_t> streamIn_t;
typedef hls::stream<fixOut_t> streamOut_t;

void fir_filter(streamIn_t* x, fixIn_t h[NUM_TAPS], streamOut_t* y);
#endif
