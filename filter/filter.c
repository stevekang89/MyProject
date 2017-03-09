#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////
//  Filter Code Definitions
//////////////////////////////////////////////////////////////

// maximum number of inputs that can be handled
// in one function call
#define MAX_INPUT_LEN   80
// maximum length of filter than can be handled
#define MAX_FLT_LEN     80
// buffer to hold all of the input samples
#define BUFFER_LEN      (MAX_FLT_LEN - 1 + MAX_INPUT_LEN)

// array to hold input samples
double insamp[ BUFFER_LEN ];

// FIR init
void firFloatInit( void )
{
    memset( insamp, 0, sizeof( insamp ) );
}

// the FIR filter function
void firFloat( double *coeffs, double *input, double *output,
        int length, int filterLength )
{
    double acc;     // accumulator for MACs
    double *coeffp; // pointer to coefficients
    double *inputp; // pointer to input samples
    int n;
    int k;
    
    // put the new samples at the high end of the buffer
    memcpy( &insamp[filterLength - 1], input,
            length * sizeof(double) );

    // apply the filter to each input sample
    for ( n = 0; n < length; n++ ) {
        // calculate output n
        coeffp = coeffs;
        inputp = &insamp[filterLength - 1 + n];
       acc = 0;
       for ( k = 0; k < filterLength; k++ ) {
            acc += (*coeffp++) * (*inputp--);
       }
        output[n] = acc;
    }
    // shift input samples back in time for next time
    memmove( &insamp[0], &insamp[length],
            (filterLength - 1) * sizeof(double) );

}


//  Test program
//////////////////////////////////////////////////////////////

// bandpass filter centred around 1000 Hz
// sampling rate = 8000 Hz


//#define FILTER_LEN  63
/*void intToFloat( int16_t *input, double *output, int length )
{
    int i;

    for ( i = 0; i < length; i++ ) {
        output[i] = (double)input[i];
    }
}

void floatToInt( double *input, int16_t *output, int length )
{
    int i;

    for ( i = 0; i < length; i++ ) {
        if ( input[i] > 32767.0 ) {
            input[i] = 32767.0;
        } else if ( input[i] < -32768.0 ) {
            input[i] = -32768.0;
        }
        // convert
        output[i] = (int16_t)input[i];
    }
}
*/
// number of samples to read per loop
#define SAMPLES   100

int main(int argc, char *argv[])
{
    if (argc==1)
    {
        fputs("Not enough argument: fir_exe input_data coeff_file output_data: warning be more accurate\n",stderr);
        fputs("looks ok\n",stderr);
        exit(1);
    }

    int size;
    int count;
    int count_coef;
    char *str_coef;
    int FILTER_LEN;
//    int16_t input[SAMPLES];
//    int16_t output[SAMPLES];
    double input[SAMPLES];
    double output[SAMPLES];
    double floatInput[SAMPLES];
    double floatOutput[SAMPLES];
    double coeffs[100];
    FILE   *in_fid;
    FILE   *out_fid;
    FILE   *coef_fid;

    // open the input file
    in_fid = fopen(argv[1], "rb" );
    if ( in_fid == 0 ) {
        printf("couldn't open %s", argv[1]);
        return 0;
    }
    // open the output file
    out_fid = fopen(argv[3], "wb" );
    if ( out_fid == 0 ) {
        printf("couldn't open %s",argv[3]);
        return 0;
    }
    // open the filter coefficient file
    coef_fid = fopen(argv[2], "rb");
    if ( coef_fid == 0) {
        printf("couldn't open %s",argv[2]);
        return 0;
    }
    
    printf("Files are opened\n<Filter coefficient>\n");

    count_coef=0;

    // read input file
    while (0<fscanf(coef_fid, "%lf\n", &coeffs[count_coef])) {
        printf("%lf\n",coeffs[count_coef]);
        count_coef++;
    }

    // read filter file
    printf("<Input values>\n");
    count=0;
    while (0<fscanf(in_fid, "%lf\n", &input[count])) {
        printf("%lf\n",input[count]);
        count++;
    }
    size = count;
    FILTER_LEN = count_coef;

    printf("Length of input: %d\n",size);
    printf("Length of filter: %d\n",FILTER_LEN);

    printf("Name of input file: %s\n", argv[1]);
    printf("Name of coefficient file: %s\n", argv[2]);
    printf("Name of output file: %s\n", argv[3]);

    // initialize the filter
    firFloatInit();

    // process all of the samples
    count=0;
    do {
      // convert to doubles
//        intToFloat( input,floatInput, size );
        // perform the filtering
       firFloat( coeffs, input, output, size,
                FILTER_LEN );
        // convert to ints
//        floatToInt( floatOutput, output, size );
        // write samples to file
        fprintf( out_fid, "%lf\n", output[count++] );

    } while ( count<size );

    fclose( in_fid );
    fclose( out_fid );

    return 0;
}
