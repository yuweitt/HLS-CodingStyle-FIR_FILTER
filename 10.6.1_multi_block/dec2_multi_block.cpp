#include "dec2_2stage.h"
#include "decimate.hpp"

void dec2_2stage(streamIn_t &x,
                fixIn_t h[NUM_TAPS],
                streamOut_t &y) {
    static streamMid_t y_int;
    //BLOCK0:dec<0,8,1,8,1,NUM_TAPS,S_RATE>(x,h,&y_int);
    //if (y_int.available(2)){
    //BLOCK1:dec<1,18,4,8,1,NUM_TAPS,S_RATE>(&y_int,h,y);
    //}
	#pragma HLS DATAFLOW
	//#pragma HLS stream variable=x depth=2
	//#pragma HLS stream variable=y_int depth=2
    static bool f0_vld_in, f0_vld_out, f1_vld_out;
    f0_vld_in = true;
    BLOCK0:dec<0,8,1,8,1,NUM_TAPS,S_RATE>(x,h,y_int,f0_vld_in,f0_vld_out);
    BLOCK1:dec<1,18,4,8,1,NUM_TAPS,S_RATE>(y_int,h,y,f0_vld_out,f1_vld_out);
 }
