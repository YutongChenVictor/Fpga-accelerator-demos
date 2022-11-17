#ifndef __CONV_CORE_H__
#define __CONV_CORE_H__

#include "ap_fixed.h"
#include <iostream>


using namespace std;

void Conv(ap_uint<16> CHin, ap_uint<16> Hin, ap_uint<16> Win, ap_uint<16> CHout, ap_uint<8> Kx, ap_uint<8> Ky, ap_uint<8> Sx, ap_uint<8> Sy, ap_uint<1> pd_mode, ap_uint<1> relu_en, float feature_in[], float conv_w[], float bias[], float feature_out[]);

#endif
