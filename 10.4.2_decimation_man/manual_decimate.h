#include "shift_class.h"
#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>
using namespace hls;

typedef ap_fixed<8, 1> fixIn_t;
typedef ap_fixed<19, 8> fixOut_t;
typedef hls::stream<fixIn_t> streamIn_t;
typedef hls::stream<fixOut_t> streamOut_t;
void dec_i1( streamIn_t *x, fixIn_t h[4], streamOut_t *y);
