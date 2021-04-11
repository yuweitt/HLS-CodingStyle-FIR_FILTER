#ifndef __DEC2_H__
#define __DEC2_H__
#include <ap_fixed.h>
#include <hls_stream.h>
#include "shift_class.h"

#define	NUM_TAPS					4
#define RATE                        2

template<int ID, int W0, int I0, int W1, int I1>
void dec2(ap_fixed<W0,I0> &x,
        ap_fixed<W1,I1> h[NUM_TAPS],
        ap_fixed<W0+W1+RATE,I0+I1+RATE> &y){
    static shift_class<ap_fixed<W0,I0>,NUM_TAPS> regs;
    ap_fixed<W0+W1,I0+I1+RATE> acc = 0;
    static ap_uint<1> cnt = 0;
    regs << x;
    MAC:for (int i = 3; i>=0; i--) {
        acc += h[i] * regs[i];
    }
    if ( cnt == 1)//Phase 1
        y = acc;
    cnt++;
}

#endif
