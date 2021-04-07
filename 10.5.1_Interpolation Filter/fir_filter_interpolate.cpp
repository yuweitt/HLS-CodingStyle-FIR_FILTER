#include "shift_class.h"
#include "fir_filter.h"
#include "interpolate.hpp"
void fir_filter(ac_channel<ac_fixed<8,1> > &x,
ac_fixed<8,1> h[4],
ac_channel<ac_fixed<18,4> > &y){
    inter<0,8,1,8,1,4,2>(x,h,y);
}