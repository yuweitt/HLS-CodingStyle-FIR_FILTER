#include "shift_class.h"
#include "fir_filter.h"
#include "interpolate.hpp"
void fir_filter(streamIn_t* x,
                fixIn_t h[NUM_TAPS],
                streamOut_t* y){
    inter<0,8,1,8,1,NUM_TAPS,S_RATE>(x,h,y);
}
