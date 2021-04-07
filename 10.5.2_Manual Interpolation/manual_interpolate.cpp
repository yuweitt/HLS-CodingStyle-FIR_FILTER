#include <ac_channel.h>
#include "shift_class.h"
#include "fir_filter.h"
#include "shift_class.h"
void fir_filter (ac_channel<ac_fixed<8,1> > &x,
ac_fixed<8,1> h[4],
ac_channel<ac_fixed<19,4> > &y){
    static shift_class<ac_fixed<8,1>,4> regs;
    static ac_fixed<19,8> temp;
    static ac_int<1,false> cnt;
    if(cnt==0)
        regs << x.read();
    else
    regs << 0;
    MAC0:for (int i = 0; i<2; i++) {
        temp += h[i*2+cnt]*regs[i*2+cnt];
    }
    y.write(temp);
    temp = 0;
    cnt++;
}