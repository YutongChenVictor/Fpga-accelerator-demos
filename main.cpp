#include "fully_connect.h"
#include "stdio.h"

int main()
{

	ap_uint<16> CHin ,Hin, Win, fc_ch;
	int map_size = 800;
	int channel_size = 5;
	CHin = 50;
	Hin = 4;
	Win = 4;
	fc_ch = 5;
	float feature_in[map_size], feature_out[channel_size], fc_w[4800],
	fc_b[channel_size];



	for (int i = 0; i < map_size; i++)
		feature_in[i] = i % 4;

	for (int i = 0; i < 4800; i++)
		fc_w[i] = 1;

	for (int i = 0; i < fc_ch; i++)
		fc_b[i] = 1;

	fully_connect(CHin, Hin, Win, fc_ch, feature_in, fc_w, fc_b, feature_out);

	for (int i = 0; i < fc_ch; i++)
		printf("feature_out[%d] = %f\n ", i, feature_out[i]);
	return 0;
}
