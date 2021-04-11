//#include <iostream>
#include <ap_fixed.h>
#include <hls_stream.h>
#include "helper.h"
#include "shift_class.h"

//using namespace std;

template<int W0, int W1, int N>
struct _WN{
enum { val = W0 + W1 + log2_ceil<N>::val };
};
template<int ID,
int W0, int I0,
int W1, int I1,
int N, int RATE>
void dec(hls::stream<ap_fixed<W0,I0> >& x,
        ap_fixed<W1,I1> h[N],
        hls::stream<ap_fixed<_WN<W0,W1,N>::val,_WN<I0,I1,N>::val> >& y,
        bool& vld_in, bool& vld_out){
    static shift_class<ap_fixed<W0,I0>,N> regs;
    ap_fixed<_WN<W0,W1,N>::val,_WN<I0,I1,N>::val> acc = 0;
    ap_fixed<W0,I0> x_int;

    ap_fixed<W0,I0> temp[RATE];
    int cnt = 0;
    static ap_uint<1> phase_cnt;

    // cout << " filter " << ID << " " << phase_cnt;

    vld_out = false;
    if (vld_in) {
        if (phase_cnt == RATE - 1)
            vld_out = true;
        phase_cnt++;
    }

    if (vld_out) {
        READ: for (int i = 0; i < RATE; i++) {
            x_int = x.read();
        }
        regs << x_int;
        MAC:for (int i = 0; i < N; i++) {
            acc += h[i] * regs[i];
        }
        y.write(acc);
    }

    vld_in = false;

}
