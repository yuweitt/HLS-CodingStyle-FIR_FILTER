#include <ap_fixed.h>
#include <hls_stream.h>
#include "helper.h"
#include "shift_class.h"

template<int W0, int W1, int N>
struct _WN{
    enum { val = W0 + W1 + log2_ceil<N>::val };
};
template<int ID,
        int W0, int I0,
        int W1, int I1,
        int N, int RATE>
void inter(hls::stream<ap_fixed<W0,I0> >* x,
            ap_fixed<W1,I1> h[N],
            hls::stream<ap_fixed<_WN<W0,W1,N>::val,_WN<I0,I1,N>::val> >* y) {
    static shift_class<ap_fixed<W0,I0>,N> regs;
    ap_fixed<_WN<W0,W1,N>::val,_WN<I0,I1,N>::val> acc = 0;

    WRITE:for (int i = 0; i < RATE; i++){
        if( i == 0)
            regs << x->read();
        else
            regs << 0;
        MAC:for (int j = 0; j < N; j++) {
            acc += h[j] * regs[j];
        }
        y->write(acc);
        acc = 0;
    }
}
