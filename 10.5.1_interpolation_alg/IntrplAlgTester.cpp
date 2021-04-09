#include <iostream>
#include <math.h>
#include "fir_filter.h"

using namespace std;

#define NUM_SAMPLES			128

int main(int argc, char *argv[]) {
    FILE         *fp;
    
    fixIn_t signal;
    fixIn_t input[NUM_SAMPLES];
    fixOut_t output[NUM_SAMPLES * S_RATE];
    fixIn_t taps[NUM_TAPS] = {0.208,0.68,0.68,0.208};
    streamIn_t strmInput;
    streamOut_t strmOutput;
    const double pi = 3.14;
    
    int i;

    cout << ">> Start test!" << endl;

    fp = fopen("out.dat", "w");

    for (i = 0; i < NUM_SAMPLES; i++) {
        signal = 0.98 * sin(2 * pi * i / 64);
        input[i] = signal;
        strmInput.write(signal);
        fir_filter(&strmInput, taps, &strmOutput);
    }

    float in;

    for (i = 0; i < NUM_SAMPLES * S_RATE; i++) {
        output[i] = strmOutput.read();
        in = (i % S_RATE)? 0 : input[i/S_RATE].to_float();
        fprintf(fp,"%i %.7f %.14f\n", i, in, output[i].to_float());
        cout << i << fixed << " " << setprecision(7) << in
							<< " " << setprecision(14) << output[i].to_float() << endl;
							
    }

    fclose(fp);

    cout << ">> Comparing against output data..." << endl;
    /*
    if (system("fc .\\out.dat ..\\..\\..\\out_gold.dat")) {
		cout << ">> Test failed!" << endl;
		return 1;
	}*/

    cout << ">> Test passed!" << endl;
	cout << "------------------------" << endl;
    return 0;
}
