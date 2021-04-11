#ifndef __DEC2_H__
#define __DEC2_H__
#include <ap_fixed.h>
#include "shift_class.h"

#define	NUM_TAPS					4
#define R_RATE                      2
#define W_RATE                      4

template<int W0, int I0, int W1, int I1>
class dec2_i2{
private:
    shift_class<ap_fixed<W0,I0>,NUM_TAPS> regs;
    ap_fixed<W0+W1,I0+I1+R_RATE> acc;
    ap_uint<2> cnt;
    bool vld;
    bool go;
public:
    dec2_i2(): vld(false), acc(0), go(false), cnt(0) {}
    bool exec(ap_fixed<W0,I0> &x,
    ap_fixed<W1,I1> h[NUM_TAPS],
    ap_fixed<W0+W1+R_RATE,I0+I1+R_RATE> &y,
    bool &vld_in, bool &vld_out){
        vld = false;
        if (vld_in)
            go = true;
        if (go) {
            if (!(cnt&1))//read with rate 2
                regs << x;
            acc += h[ cnt + 2 - (cnt[1] << 2)] * regs[cnt + (1 >> cnt[1]) - cnt[1]];
            if(cnt == W_RATE - 1){//write with rate 4
                y = acc;
                acc = 0;
                vld = true;
            }
            cnt++;
            vld_out = vld;
        }
    }
};
#endif
