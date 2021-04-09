#include <iostream>
#include <math.h>
#include "dec2_2stage.h"

using namespace std;

#define NUM_SAMPLES			128

int main(int argc, char *argv[]) {
    FILE         *fp;

    fixIn_t signal;
    fixIn_t input[NUM_SAMPLES];
    fixOut_t out;
    fixOut_t output[NUM_SAMPLES];
    fixIn_t taps[NUM_TAPS] = {0.208,0.68,0.68,0.208};
    const double pi = 3.14;
    
    int i;

    cout << ">> Start test!" << endl;

    fp = fopen("out.dat", "w");
    for (i = 0; i < NUM_SAMPLES; i++) {
        signal = 0.98 * sin(2 * pi * i / 64);
        input[i] = signal;
        out = 0;
        dec2_2stage(signal, taps, out);
        output[i] = out;
    }


    for (i = 0; i < NUM_SAMPLES; i++) {
        fprintf(fp,"%i %.7f %.21f\n", i, input[i].to_float(), output[i].to_float());
        	cout << i << fixed << " " << setprecision(7) << input[i].to_float()
							<< " " << setprecision(21) << output[i].to_float() << endl;
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
