//
//  main.c
//  testprog1
//
//  Created by Jules Pierce on 6/3/15.
//  Copyright (c) 2015 Jules Pierce. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "bmp_io.h"
#include "imgstuff.h"

int main(int argc, char * argv[]) {
    FILE *in_fd;
    unsigned char in_dat[1];
    int byte_count[256];
    int i, j;
    double total;
    double prob[256];
    double mean=0;
    double mean_sq = 0;
    double count;
    double var;
    double entr;
    double total_prob = 0;
    unsigned char *picdat;
    int rows, cols;
    char filename[100];
    int bang[256];
    double psum;


	if( argc != 4){
		printf("usage is: %s pic_type in_filename out_filename\n", argv[0] );
		exit(1);
	}
    input_bmp (argv[2], &cols, &rows, &picdat, MONO);
    
    for (i = 0; i < 256; i++) byte_count[i] = 0;
    
    for (i = 0; i < rows; i++){
        for (j = 0; j < cols; j++){
            byte_count[picdat[mi (i, j, cols)]]++;
        }
    }
    
    total = rows * cols;
    
    sprintf(filename, "%s_m.txt", argv[3]);
    in_fd = fopen(filename, "w");
    for (i=0; i < 256; i++){
        prob[i] = byte_count[i]/total;
        //printf("%d    %f\n", i, prob[i]);
        fprintf(in_fd, "%10.6e    %10.6e\n", (double)i, prob[i]);
        total_prob += prob[i];
        mean += i * prob[i];
        mean_sq += i*i * prob[i];
    }
    var = mean_sq - mean*mean;
    printf("total_prob = %lf  mean = %lf var = %lf\n", total_prob, mean, var);
    
    psum = 0;
    for (i = 0; i < 256; i++){
        psum += prob [i];
        bang [i] = 255.0 * psum;
    }
    
    for (i = 0; i < rows; i++){
        for (j = 0; j < cols; j++){
            picdat [mi (i, j, cols)] = bang [picdat [mi (i, j, cols)]];
        }
    }
    output_bmp (argv[3], cols, rows, picdat, MONO);
    
    
    free (picdat);
    fclose(in_fd);
    




}
