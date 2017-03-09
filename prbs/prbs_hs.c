#include "nec.h"
#include "dec_to_bin.h"

void prbs_hs(uint8_t *seq, uint8_t start_state, int len)
{
    uint8_t reg = start_state;
    bool newbit;
    int count=0;
    char *bin;

    while (1) {
        // taps: 7 6
        newbit = ;
        reg = ((reg<<1) | newbit) & 0x7f;
        seq[count] = newbit;
        printf("New bit: %d\t\t",newbit);
        bin = dec_to_bin(reg,7);
        printf("Reg: ");
        for (int i=0; i<8; i++) {
            printf("%c", bin[i]);
        }
        printf("\n");
        count++;
        if (count == len)
            break;
    }
    free(bin);
}
