#include <iostream>
#include <math.h>
#include "dec2_2stage.h"

using namespace std;

#define NUM_SAMPLES			128

int main(int argc, char *argv[]) {
    FILE         *fp;

    fixIn_t signal;
    fixIn_t input[NUM_SAMPLES];
    fixOut_t output[NUM_SAMPLES];
    fixIn_t taps[NUM_TAPS] = {0.208,0.68,0.68,0.208};
    streamIn_t strmInput;
    streamOut_t strmOutput;
    const double pi = 3.14;
    
    int i;

    int inRate = 4;
    int rRate = 2, wRate = 4;                   				// dec2
    int f0_cRate = 2; 											// inRate / rRate,
    int f1_cRate = 4; 			                				// inRate / rRate * wRate / rRate;
    int f0_cycles = inRate / rRate * wRate;						// 8
    int f1_cycles = f0_cycles / rRate * wRate;  				// 16
    int f0_offset = 1 + (wRate - 1) * f0_cRate;					// 7, at i^th cycle produce first output
    int f1_offset = (f0_offset + 1) + (wRate - 1) * f1_cRate;	// 20

    cout << ">> Start test!" << endl;

    fp = fopen("out.dat", "w");

    for (i = 0; i < NUM_SAMPLES; i++) {
        signal = 0.98 * sin(2 * pi * i / 64);
        input[i] = signal;
        if (i % inRate == 0) { strmInput.write(signal); }
        dec2_2stage(&strmInput, taps, &strmOutput);
    }

    float out;

    out = 0;
    for (i = 0; i < f1_offset - 1; i++) {
        fprintf(fp,"%i %.7f %.21f\n", i, input[i].to_float(), out);
    	cout << i << fixed << " " << setprecision(7) << input[i].to_float()
                            << " " << setprecision(21) << out << endl;
    }
    for (i = f1_offset - 1; i < NUM_SAMPLES; i++) {
        out = 0;
        if (i % f1_cycles == (f1_offset - 1) % f1_cycles) {
            out = strmOutput.read();
        }
        fprintf(fp,"%i %.7f %.21f\n", i, input[i].to_float(), out);
    	cout << i << fixed << " " << setprecision(7) << input[i].to_float()
                            << " " << setprecision(21) << out << endl;
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
