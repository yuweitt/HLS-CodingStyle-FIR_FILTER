#include "shift_class.h"
#include "manual_decimate.h"
#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>

using namespace std;
using namespace hls;
void dec_i1( streamIn_t *x,
		fixIn_t h[4],
		streamOut_t *y){
    static shift_class<fixIn_t ,4 > regs;
    static fixOut_t acc;
    static ap_uint<1> cnt;
    fixIn_t rd;

    regs << x->read();

    MAC0:for (int i = 0; i<2; i++) {
        acc += h[i+((1-cnt)<<1)]*regs[i+1-cnt];
    }
    if(cnt==1){
        y->write(acc);
        acc = 0;
    }
    cnt++;
}
