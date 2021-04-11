//#include "dec2_alg.h"
#include "dec2_2stage.h"

void dec2_2stage(fixIn_t &x,
                fixIn_t h[NUM_TAPS],
                fixOut_t &y) {
    static fixMid_t y0_int = 0;
    static uint2_t cnt;
    uint2_t sel;
    if ( !cnt[0] ) {//sel for cnt==0 and cnt==2
        sel = 0;

    } else if( cnt == 3 ) {
        sel = 1;
    } else {
        sel = 2;
    }
    /*
    } else {
    	sel = 1;
    }*/
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
