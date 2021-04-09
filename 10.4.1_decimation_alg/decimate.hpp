#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>
#include "shift_class.h"
#include "helper.h"
template<int W0, int W1, int N>
struct _WN{
enum { val = W0 + W1 + log2_ceil<N>::val  };
};
template<int ID,
    int W0, int I0,
    int W1, int I1,
    int N, int RATE>
#pragma hls_design block
void dec(hls::stream<ap_fixed<W0,I0> > *x,
ap_fixed<W1,I1> h[N],
hls::stream<ap_fixed<_WN<W0,W1,N>::val,_WN<I0,I1,N>::val> > *y){
    static shift_class<ap_fixed<W0,I0>,N> regs;
    ap_fixed<_WN<W0,W1,N>::val,_WN<I0,I1,N>::val> acc = 0;
    ap_fixed<W0,I0> x_int;
    // return if FIFO size >= 2

    if (!x->empty()){
        READ:for(int i=0;i<RATE;i++)
        x_int = x->read();
        regs << x_int;
        MAC:for (int i = 0; i<N; i++) {
            acc += h[i]*regs[i];
        }
        y->write(acc);
    }
}

