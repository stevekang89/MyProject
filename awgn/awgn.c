#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void awgn(double *sample, double power, int len)
{
    int i, j;
    int sum;
    double mean;
    double var;
    int num;
    int lim_num;

    srand(time(NULL));
    double data;
    double temp;

    num = 100;
    lim_num = 1;
    for (i=0; i<len; i++) {
        data = 0;
        for (j=0; j<num; j++) {
		data += ((double)rand()/RAND_MAX * (lim_num));
        }
	data = data - num/2;
//	printf("row data %lf\t\t",data);
	data = data/sqrt(lim_num*lim_num*num/12);
        data = data * sqrt(power);
//        printf("power allocated data %lf\n",data);
        sample[i] = data;
    }
}

