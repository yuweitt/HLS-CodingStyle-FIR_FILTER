#ifndef _DEC2_H
#define _DEC2_H
#include <ac_fixed.h>
#include "shift_class.h"
template<int W0, int I0, int W1, int I1>
class dec2_i2{
private:
    shift_class<ac_fixed<W0,I0>,4> regs;
    ac_fixed<W0+W1,I0+I1+2> acc;
    ac_int<2,false> cnt;
    bool vld;
    bool go;
public:
    dec2_i2():vld(false), acc(0), go(false), cnt(0){}
    bool exec(ac_fixed<W0,I0> &x,
    ac_fixed<W1,I1> h[4],
    ac_fixed<W0+W1+2,I0+I1+2> &y,
    bool &vld_in, bool &vld_out){
        vld = false;
        if(vld_in)
            go = true;
        if(go){
            if(!(cnt&1))//read with rate 2
                regs << x;
            acc += h[cnt + 2 - (cnt[1]<<2)]*regs[cnt+(1>>cnt[1])-cnt[1]];
            if(cnt==3){//write with rate 4
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