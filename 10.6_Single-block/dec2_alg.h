#include <ac_channel.h>
#include <ac_fixed.h>
#include "shift_class.h"
template<int ID, int W0, int I0, int W1, int I1>
void dec2(ac_fixed<W0,I0> &x,
ac_fixed<W1,I1> h[4],
ac_fixed<W0+W1+2,I0+I1+2> &y){
    static shift_class<ac_fixed<W0,I0>,4> regs;
    ac_fixed<W0+W1,I0+I1+2> acc = 0;
    static ac_int<1,0> cnt;
    regs << x;
    MAC:for (int i = 3; i>=0; i--) {
        acc += h[i]*regs[i];
    }
    if(cnt==1)//Phase 1
        y = acc;
    cnt++;
}