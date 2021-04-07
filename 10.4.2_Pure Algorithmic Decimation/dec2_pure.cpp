#include <ac_channel.h>
#include <ac_fixed.h>
#include "shift_class.h"
void dec2(ac_channel< ac_fixed<8,1> > &x,
ac_fixed<8,1> h[4],
ac_channel< ac_fixed<19,4> > &y){
    static shift_class<ac_fixed<8,1>,4> regs;
    ac_fixed<19,8> temp = 0;
    static ac_int<1,0> cnt;

    regs << x.read();
    MAC:for (int i = 0; i<4; i++) {
        temp += h[i]*regs[i];
    }
    if(cnt==1)//Phase 1
        y.write(temp);
    cnt++;
}