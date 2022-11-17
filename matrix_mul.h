#ifndef __MATRIX_MUL_H__
#define __MATRIX_MUL_H__

#include "ap_fixed.h"
#include "stdio.h"
void matrix_mul(ap_int<8> A[4][4], ap_int<8> B[4][4], ap_int<16> C[4][4]);
#endif
