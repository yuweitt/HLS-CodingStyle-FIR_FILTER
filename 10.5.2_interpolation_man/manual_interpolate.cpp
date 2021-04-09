#include "fir_filter.h"
#include "shift_class.h"
void fir_filter(streamIn_t* x,
                fixIn_t h[NUM_TAPS],
                streamOut_t* y) {
    static shift_class<fixIn_t, NUM_TAPS> regs;
    static fixOut_t temp;
    static uint1_t cnt;
    if (cnt == 0)
        regs << x->read();
    else
        regs << 0;
    MAC0:for (int i = 0; i < S_RATE; i++) {
        temp += h[ i * S_RATE + cnt] * regs[ i * S_RATE + cnt];
    }
    y->write(temp);
    temp = 0;
    cnt++;
}