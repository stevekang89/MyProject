#include "prbs.h"
#include "dec_to_bin.h"
#include "nec.h"

void main() {
    int len;
    uint8_t *seq;
    uint8_t start_state;
    FILE *out_fid;
    
    // Random reg. generation
    srand(time(NULL));
    start_state = (double)rand()/RAND_MAX*127;
    printf("Initial reg.: %d\n",start_state);

    // Open the output file
    out_fid = fopen("output.txt", "wb");
    if (out_fid == 0) {
        printf("could't open");
    }


    // Determine the seq. length & mem. allocation
    printf("Enter the length of sequence: ");
    scanf("%d",&len);
    seq = (uint8_t *) malloc (len * sizeof(uint8_t));
    printf("Memory is allocated.\n");

/*    // PRBS generation
    prbs(seq, start_state, len);
    printf("Ourput sequence [prbs]: ");
    for (int i=0; i<len; i++) {
        printf("%d",seq[i]);
    }
    printf("\n");

    prbs_hs(seq, start_state, len);
    printf("Ourput sequence [prbs_hs]: ");
    for (int i=0; i<len; i++) {
        printf("%d",seq[i]);
    }
    printf("\n");
*/

    prbs(seq, start_state, len);
    printf("Ourput sequence: ");
    for (int i=0; i<len; i++) {
        printf("%d",seq[i]);
        fprintf( out_fid,"%d\n",seq[i]);
    }
    printf("\n");

    fclose(out_fid);
    free(seq);
}
