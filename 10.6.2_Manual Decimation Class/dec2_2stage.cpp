#include <ac_channel.h>
#include "dec2_i2.hpp"
void dec2_2stage(ac_channel<ac_fixed<8,1> > &x,
ac_fixed<8,1> h[4],
ac_channel<ac_fixed<28,7> > &y){
    static ac_fixed<18,4> y0_int;
    ac_fixed<28,7> y1_int;
    ac_fixed<8,1> x_int;
    static ac_int<4,false> phase_cnt;
    static ac_int<2,0> sel_phase;
    static dec2_i2<8,1,8,1> f0;
    static dec2_i2<18,4,8,1> f1;
    static bool f0_vld_in, f0_vld_out, f1_vld_out;

    if(!phase_cnt[0])//if even counts
        sel_phase = 0;
    else if(phase_cnt.slc<2>(0)==3)//if every 4th odd count
        sel_phase = 1;

    else
        sel_phase = 3;//do nothing
    if(phase_cnt.slc<2>(0)==0){//read a rate of 4
        x_int = x.read();
        f0_vld_in = true;
    }else
        f0_vld_in = false;
    switch(sel_phase){
        case 0:
            f0.exec(x_int,h,y0_int,f0_vld_in,f0_vld_out);
            break;
        case 1:
            f1.exec(y0_int,h,y1_int,f0_vld_out, f1_vld_out);
            if(f1_vld_out)
                y.write(y1_int);
            break;
        default:
            break;
    }
    phase_cnt++;
}