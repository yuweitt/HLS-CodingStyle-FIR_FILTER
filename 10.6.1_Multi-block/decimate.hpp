#include <ac_fixed.h>
#include <ac_channel.h>
#include "shift_class.h"
template<int W0, int W1, int N>
struct _WN{
enum { val = W0 + W1 + ac::log2_ceil<N>::val };
};
template<int ID,
int W0, int I0,
int W1, int I1,
int N, int RATE>
#pragma hls_design block
void dec(ac_channel<ac_fixed<W0,I0> > &x,
ac_fixed<W1,I1> h[N],
ac_channel<ac_fixed<_WN<W0,W1,N>::val,_WN<I0,I1,N>::val> > &y){
    static shift_class<ac_fixed<W0,I0>,N> regs;
    ac_fixed<_WN<W0,W1,N>::val,_WN<I0,I1,N>::val> acc = 0;
    ac_fixed<W0,I0> x_int;

    if (x.available(2)){
        READ:for(int i=0;i<RATE;i++)
            x_int = x.read();
        regs << x_int;
        MAC:for (int i = 0; i<N; i++) {
            acc += h[i]*regs[i];
        }
        y.write(acc);
    }
}