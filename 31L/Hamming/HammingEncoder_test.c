#include<stdio.h>
#include<math.h>
#include "svdpi.h"
#include "vpi_user.h"



void encoder(
                int data_in,
                int* data_out,
                int* parity_out
		
		)
{
    int i, a[10], c[4], r[14], clk[4], n, sum = 0;
    printf("%d\n", data_in);
    //int *a = (int *)svGetArrayPtr(data_in);
    a[0]= data_in & 1;
    a[1]= data_in>>1 & 1;
    a[2]= data_in>>2 & 1;
    a[3]= data_in>>3 & 1;
    a[4]= data_in>>4 & 1;
    a[5]= data_in>>5 & 1;
    a[6]= data_in>>6 & 1;
    a[7]= data_in>>7 & 1;
    a[8]= data_in>>8 & 1;
    a[9]= data_in>>9 & 1;
    a[10] =data_in>>10 & 1;
    printf("%x\n", data_in&(512));    
    //printf("%x\n", a[5]);
    //printf("%x\n", a[3]);
    //printf("%x\n", a[2]);
    //printf("%x\n", a[9]);
    printf("%x\n", a[0]);


    c[0]=(a[10-0] ^ a[10-1] ^ a[10-3] ^ a[10-4] ^ a[10-6] ^ a[10-8] ^ a[10-10]);
    c[1]=(a[10-0] ^ a[10-2] ^ a[10-3] ^ a[10-5] ^ a[10-6] ^ a[10-9] ^ a[10-10]);
    c[2]=(a[10-1] ^ a[10-2] ^ a[10-3] ^ a[10-7] ^ a[10-8] ^ a[10-9] ^ a[10-10]);
    c[3]=(a[10-4] ^ a[10-5] ^ a[10-6] ^ a[10-7] ^ a[10-8] ^ a[10-9] ^ a[10-10]);

    printf("data bits after hamming code is\n");

    for(i=10;i>=0;i--) {
        printf("%d",a[i]);
    }
    printf("\n");
    for(i=3;i>=0;i--) {
        printf("%d",c[i]);
    }
    printf("\n");
    *data_out = data_in;


    *parity_out = ((c[0]&1) << 3) | ((c[1]&1) << 2) | ((c[2]&1) << 1) | ((c[3]&1));
}

