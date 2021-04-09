//#ifndef __FIR_FILTER_H__
//#define __FIR_FILTER_H__

#include "shift_class.h"
#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>
#include "decimate.hpp"

#define TAP	4
#define SAMPLE_RATE 	2

typedef ap_fixed<8, 1> fixIn_t;
typedef ap_fixed<18, 4> fixOut_t;
typedef hls::stream<fixIn_t> streamIn_t;
typedef hls::stream<fixOut_t> streamOut_t;

void fir_filter(streamIn_t *x, fixIn_t h[TAP], streamOut_t *y);

//#endif
