#include "pooling.h"

#define max(a,b) ((a > b) ? a : b)

void pooling(ap_uint<16> CHin, ap_uint<16> Hin, ap_uint<16> Win, ap_uint<8> Kx, ap_uint <8> Ky, ap_uint<1> mode, float feature_in[],float feature_out[])
{
	#pragma HLS INTERFACE s_axilite port=Kx
	#pragma HLS INTERFACE s_axilite port=Ky
	#pragma HLS INTERFACE s_axilite port=CHin
	#pragma HLS INTERFACE s_axilite port=Hin
	#pragma HLS INTERFACE s_axilite port=mode
	#pragma HLS INTERFACE s_axilite port=Win
	#pragma HLS INTERFACE m_axi depth=4294967295 port=feature_out
	#pragma HLS INTERFACE m_axi depth=4294967295 port=feature_in
	#pragma HLS INTERFACE s_axilite port=return
	ap_uint<16> Hout,Wout;

	Hout = Hin / Kx;
	Wout = Win / Ky;

	for (int c = 0; c < CHin; c++)
		for (int i = 0; i < Hout; i++)
			for (int j = 0; j < Wout; j++)
			{
				float sum;

				if (mode == 0)
					sum = 0;
				else
					sum = -9999999999999;
				for (int ii = 0; ii < Ky; ii++)
					for (int jj = 0; jj < Kx; jj++)
					{
						ap_uint <16> h = i * Ky + ii;
						ap_uint <16> w = j * Kx + jj;

						if (!mode)
							sum = sum + feature_in[h * CHin * Win + w * CHin + c];
						else
							sum = max(sum, feature_in[h * CHin * Win + w * CHin + c]);
					}
				if (!mode)
					sum = sum / (Kx * Ky);
				feature_out[i * CHin * Win + j * CHin + c] = sum;
			}
}
