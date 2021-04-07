#include "decimate.hpp"
void dec2_2stage(ac_channel<ac_fixed<8,1> > &x,
ac_fixed<8,1> h[4],
ac_channel<ac_fixed<28,7> > &y){
static ac_channel<ac_fixed<18,4> > y_int;

BLOCK0:dec<0,8,1,8,1,4,2>(x,h,y_int);
//if (y_int.available(2)){
BLOCK1:dec<1,18,4,8,1,4,2>(y_int,h,y);
 //}
 }