#include "matrix_mul.h"
void matrix_mul(ap_int<8> A[4][4], ap_int<8> B[4][4], ap_int<16> C[4][4])
{
	#pragma HLS INTERFACE s_axilite port=return
	#pragma HLS INTERFACE s_axilite port=C
	#pragma HLS INTERFACE s_axilite port=B
	#pragma HLS INTERFACE s_axilite port=A
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			#pragma HLS PIPELINE
			C[i][j] = 0;
			for (int k = 0; k < 4; k++)
			{
				#pragma HLS UNROLL
				C[i][j] = C[i][j] + A[i][k] * B[k][j];
			}
		}
}
