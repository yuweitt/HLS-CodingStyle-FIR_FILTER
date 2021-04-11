#include <iostream>
#include <math.h>
#include "dec2_2stage.h"

using namespace std;

#define NUM_SAMPLES			128

int main(int argc, char *argv[]) {
    FILE         *fp;

    fixIn_t signal;
    fixIn_t input[NUM_SAMPLES];
    fixOut_t output[NUM_SAMPLES / T_RATE];
    fixIn_t taps[NUM_TAPS] = {0.208,0.68,0.68,0.208};
    streamIn_t strmInput;
    streamOut_t strmOutput;
    const double pi = 3.14;
    
    int i, j;

    cout << ">> Start test!" << endl;

    fp = fopen("out.dat", "w");

    for (i = 0; i < NUM_SAMPLES; i++) {
        signal = 0.98 * sin(2 * pi * i / 64);
        input[i] = signal;
        strmInput.write(signal);
        cout << i;
        dec2_2stage(strmInput, taps, strmOutput);
        cout << endl;
    }

    float out;

    for (i = 0; i * T_RATE < NUM_SAMPLES; i++) {
    	output[i] = strmOutput.read();

    	for (j = 0;( j < T_RATE && (i * T_RATE + j) < NUM_SAMPLES); j++) {
    		out = (j == T_RATE - 1)? output[i].to_float() : 0;
    		int k = i * T_RATE + j;
        	fprintf(fp,"%i %.7f %.21f\n", k, input[k].to_float(), out);
        	cout << k << fixed << " " << setprecision(7) << input[k].to_float()
							<< " " << setprecision(21) << out << endl;
    	}
    }

    fclose(fp);

    cout << ">> Comparing against output data..." << endl;
    
    if (system("fc .\\out.dat ..\\..\\..\\out_gold.dat")) {
		cout << ">> Test failed!" << endl;
		return 1;
    }

    cout << ">> Test passed!" << endl;
	cout << "------------------------" << endl;
    return 0;
}
