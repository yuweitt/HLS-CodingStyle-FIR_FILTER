#include <ac_channel.h>
#include "shift_class.h"
#include "fir_filter.h"
void dec_i1(ac_channel<ac_fixed<8,1> > &x,
ac_fixed<8,1> h[4],
ac_channel<ac_fixed<19,4> > &y){
    static shift_class<ac_fixed<8,1>,4> regs;
    static ac_fixed<19,8> acc;
    static ac_int<1,false> cnt;

    regs << x.read();
    MAC0:for (int i = 0; i<2; i++) {
        acc += h[i+((1-cnt)<<1)]*regs[i+1-cnt];
    }
    if(cnt==1){
        y.write(acc);
        acc = 0;
    }
    cnt++;
}