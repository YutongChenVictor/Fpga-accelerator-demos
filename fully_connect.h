#ifndef __FULLY_CONNECT_H__
#define __FULLY_CONNECT_H__

#include "ap_fixed.h"
#include <iostream>

void fully_connect(ap_uint<16> CHin, ap_uint<16> Hin, ap_uint<16> Win, ap_uint<16> fc_ch, float feature_in[], float fc_w[], float fc_b[], float feature_out[]);


#endif
