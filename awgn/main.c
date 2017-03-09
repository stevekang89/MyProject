#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "TX.h"

#define sample_len  10000

void awgn(double *sample, double power, int len);

void main(){

    int i;
    int j;

    double sample[sample_len];
    double power;

    double sum=0;
    double var=0;
	
    FILE *out_fid;

    printf("Enter the power: ");
    scanf("%lf",&power);

    out_fid = fopen("output.txt", "wb" );
    if ( out_fid == 0 ) {
        printf("couldn't open");
    }

    awgn(sample, power, sample_len);

    // sum
    for (i=0; i<sample_len; i++) {
        sum += sample[i];
	fprintf( out_fid, "%lf\n", sample[i] );
    }
    printf("Mean of samples: %lf\n", sum/sample_len);        

    // var
    for (j=0; j<sample_len; j++) {
        var += sample[j]*sample[j];
    }
    var = var/sample_len - (sum/sample_len)*(sum/sample_len);
    printf("Power of samples: %lf\n", var);

    fclose( out_fid );
}
