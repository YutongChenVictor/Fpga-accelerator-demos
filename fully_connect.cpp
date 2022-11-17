#include "fully_connect.h"

void fully_connect(ap_uint<16> CHin, ap_uint<16> Hin, ap_uint<16> Win, ap_uint<16> fc_ch,
		float feature_in[], float fc_w[], float fc_b[], float feature_out[])
{
#pragma HLS INTERFACE m_axi depth=4294967295 port=feature_out
#pragma HLS INTERFACE m_axi depth=4294967295 port=fc_b
#pragma HLS INTERFACE m_axi depth=4294967295 port=fc_w
#pragma HLS INTERFACE m_axi depth=4294967295 port=feature_in
#pragma HLS INTERFACE s_axilite port=Win
#pragma HLS INTERFACE s_axilite port=fc_ch
#pragma HLS INTERFACE s_axilite port=Hin
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE s_axilite port=CHin
	float sum = 0;
	for (int FC_CH = 0; FC_CH < fc_ch; FC_CH++)
	{
		sum = 0;
		for (int j = 0; j < CHin; j++)
			for (int i = 0; i < Hin * Win; i++)
				#pragma HLS UNROLL
				sum = sum +  feature_in[j * Hin * Win + i] * fc_w[j * Hin * Win + i];
		sum = sum + fc_b[FC_CH];
		feature_out[FC_CH] = sum;
	}

}
