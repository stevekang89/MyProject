#include "nec.h"

char *dec_to_bin(int dec, int bin_len)
{
    int k = bin_len-1;
    char *bin;

    bin = (char *) malloc (bin_len * sizeof(char));

    while (k >= 0) {
//        printf("Current dec: %d\t\t",dec);
        bin[k] = dec & 0x00000001 ? '1' : '0';
//        printf("Current bin: %c\n",bin[k]);
        dec = dec >> 1;
        k--;
    }
    return bin;
}
