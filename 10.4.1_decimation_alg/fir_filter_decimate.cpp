#include "fir_filter.h"
#include "shift_class.h"

void fir_filter(streamIn_t *x,
fixIn_t  h[TAP],
streamOut_t *y){
	dec<0,8,1,8,1,TAP,SAMPLE_RATE>(x ,h ,y);
}
