#ifndef __POOLING_H
#define __POOLING_H


#include "ap_fixed.h"

void pooling(ap_uint<16> CHin, ap_uint<16> Hin, ap_uint<16> Win, ap_uint<8> Kx, ap_uint <8> Ky, ap_uint<1> mode, float feature_in[],float feature_out[]);

#endif
