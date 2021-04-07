#include "dec2_alg.h"
void dec2_2stage(ac_fixed<8,1> &x,
ac_fixed<8,1> h[4],
ac_fixed<28,7> &y){
    static ac_fixed<18,4> y0_int=0;
    static ac_int<2,false> cnt;
    ac_int<2,false> sel;
    if(!cnt[0])//sel for cnt==0 and cnt==2
        sel = 0;
    else if(cnt==3)
        sel = 1;
    else
        sel = 2;
    switch(sel){
        case 0:
            dec2<0>(x,h,y0_int);//read x every 4 clocks with II=2
            break;
        case 1:
            dec2<1>(y0_int,h,y);
            break;
        default:
            break;
    }
    cnt++;
}