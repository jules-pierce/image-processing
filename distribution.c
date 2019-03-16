
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "bmp_io.h"
#include "imgstuff.h"

typedef enum {FOR_NORMAL, FOR_UNIFORM} distribution_t;

double getN01 ();
double getU01 (distribution_t normal, int i);

int main(int argc, char *argv[] ){
	int i, j;
    double x1, x2;
    double y1, y2;
	unsigned int start_seed;
    int *bins;
    int num_bin;
    double low_lim, upp_lim;
    double range;
    double bin_size;
    distribution_t uniform = FOR_UNIFORM;
    
    if ( argc != 4){
        fprintf( stderr, "usage is: %s start_seed distribution_type num_bin\n", argv[0]);
        exit (1);
    }
    
    num_bin = atoi (argv [3]);
    low_lim = -5;
    upp_lim = 5;
    
    bins = (int*)malloc (num_bin * sizeof (int));
    
    for (i = 0; i < num_bin; i++){
        bins [i] = 0;
    }
    

    start_seed = atoi( argv[1] );
    srand (start_seed);
    //printf("RAND_MAX = %d\n", i = RAND_MAX);
    
    range = upp_lim - low_lim;
    bin_size = range/num_bin;
    //printf ("range = %lf  bin_size = %lf\n", range, bin_size);
    
    for (i = 0; i < 100000; i++){
        if (strcmp ("normal", argv[2]) == 0){
            y1 = getN01 ();
            //printf ("y1 = %lf\n", y1);
            if (y1 <= low_lim) {
                bins [0] ++;
            }
            else if (y1 >= upp_lim) {
                bins [num_bin - 1]++;
            }
            else {
                bins [(int)((y1-low_lim)/(bin_size))] ++;
            }
        }
        else if(strcmp ("uniform", argv[2]) == 0) {
            y1 = getU01(uniform, i);
            //printf ("y1 = %lf\n", y1);
            if (y1 <= low_lim) {
                bins [0] ++;
            }
            else if (y1 >= upp_lim) {
                bins [num_bin - 1]++;
            }
            else {
                bins [(int)((y1-low_lim)/(bin_size))] ++;
            }
        }
        else {
            printf ("error: invalid distribution type\n");
            exit (1);
        }
    }
    
    for (i = 0; i < num_bin; i++){
        printf ("%6lf    %6d\n", low_lim + i*bin_size, bins[i]);
    }

}

double getN01 (){
    static double y2;
    double y1, x1, x2;
    static int first_call = 1;
    distribution_t normal = FOR_NORMAL;
    
    if (first_call == 1){
        x1 = getU01 (normal, 1);
        x2 = getU01 (normal, 1);
        //printf ("x1 = %lf  x2 = %lf\n", x1, x2);
        //printf ("in first_call loop\n");
        y1 = (sqrt (-2 * log (x1))) * cos (6.283 * x2);
        y2 = (sqrt (-2 * log (x1))) * sin (6.283 * x2);
        first_call = 0;
        return y1;
              
    }
    else {
        first_call = 1;
        return y2;
                  
    }
    
}

double getU01 (distribution_t normal, int i){
    double x1;
    
    if (normal == FOR_NORMAL){
        x1 = (double)(rand())/RAND_MAX;
        //printf("x = %lf\n", x1);
    }
    else {
        x1 = (pow (-1, i) * 5 * ((double)(rand())/RAND_MAX));
    }
    return x1;
}

