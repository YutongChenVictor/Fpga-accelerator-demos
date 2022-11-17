#include "conv_core.h"

void Conv(ap_uint<16> CHin, ap_uint<16> Hin, ap_uint<16> Win, ap_uint<16> CHout, ap_uint<8> Kx, ap_uint<8> Ky, ap_uint<8> Sx, ap_uint<8> Sy, ap_uint<1> pd_mode, ap_uint<1> relu_en, float feature_in[], float conv_w[], float bias[], float feature_out[])
{
	#pragma HLS INTERFACE s_axilite port=return
	#pragma HLS INTERFACE s_axilite port=Sy
	#pragma HLS INTERFACE s_axilite port=Ky
	#pragma HLS INTERFACE s_axilite port=Hin
	#pragma HLS INTERFACE m_axi depth=4294967295 port=conv_w
	#pragma HLS INTERFACE s_axilite port=pd_mode
	#pragma HLS INTERFACE m_axi depth=4294967295 port=feature_in
	#pragma HLS INTERFACE s_axilite port=CHout
	#pragma HLS INTERFACE s_axilite port=Sx
	#pragma HLS INTERFACE s_axilite port=relu_en
	#pragma HLS INTERFACE m_axi depth=4294967295 port=feature_out
	#pragma HLS INTERFACE s_axilite port=CHin
	#pragma HLS INTERFACE m_axi depth=4294967295 port=bias
	#pragma HLS INTERFACE s_axilite port=Win
	#pragma HLS INTERFACE s_axilite port=Kx
	ap_uint<8> pad_x, pad_y;

	if (pd_mode)
	{
		pad_x = (Kx - 1) / 2;
		pad_x = (Ky - 1) / 2;
	}
	else
	{
		pad_x = 0;
		pad_x = 0;
	}

	ap_uint<16> Hout, Wout;

	Hout = (Hin + 2 * pad_y - Ky) / Sy + 1;
	Wout = (Win + 2 * pad_x - Kx) / Sx + 1;

	for (int cout = 0; cout < CHout; cout++)
		for (int i = 0; i < Hout; i++)
			for (int j = 0; j < Wout; j++)
			{
				float sum = 0;
				for (int ii = 0; ii < Ky; ii++)
					for (int jj = 0; ii < Kx; jj++)
					{
						ap_uint<16> h = i * Sy - pad_y + ii;
						ap_uint<16> w = j * Sy - pad_y + jj;

						if (h >= 0 && w >= 0 && h < Hin && w < Win)
						{
							for (int cin = 0; cin < CHin; cin++)
							{
								float tp = feature_in[h * CHin * Win + w * CHin + cin] * conv_w[ii * Kx * CHin * CHout + jj * CHin * CHout + cin * CHout + cout];
								sum = sum + tp;
							}
						}
					}
				sum = sum + bias[cout];
				if (relu_en && sum <= 0)
					sum = 0;
				feature_out[i * Wout * CHout + j * CHout+ cout] = sum;
			}

}
