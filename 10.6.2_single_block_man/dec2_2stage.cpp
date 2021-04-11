//#include <hls_stream.h>
//#include "dec2_i2.hpp"
#include <math.h>
#include "dec2_2stage.h"

void dec2_2stage(streamIn_t* x,
                fixIn_t h[4],
                streamOut_t* y){
    static fixMid_t y0_int;
    fixOut_t y1_int;
    fixIn_t x_int;
    static ap_uint<4> phase_cnt;
    static ap_uint<2> sel_phase;
    static dec2_i2<8,1,8,1> f0;
    static dec2_i2<18,4,8,1> f1;
    static bool f0_vld_in, f0_vld_out, f1_vld_out;

    if(!phase_cnt[0])//if even counts
        sel_phase = 0;
    else if (phase_cnt % 4 == 3)//if every 4th odd count
        sel_phase = 1;
    else
        sel_phase = 3;//do nothing


    if ( phase_cnt % 4 == 0 ){//read at rate of 4
        x_int = x->read();
        f0_vld_in = true;
    } else
        f0_vld_in = false;
    switch(sel_phase){
        case 0:
            f0.exec(x_int,h,y0_int,f0_vld_in,f0_vld_out);
            break;
        case 1: 
            f1.exec(y0_int,h,y1_int,f0_vld_out, f1_vld_out);
            if(f1_vld_out) {
                y->write(y1_int);
            }
            break;
        default:
            break;
    }
    phase_cnt++;
}
