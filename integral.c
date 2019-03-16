#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "bmp_io.h"
#include "imgstuff.h"

//rows = y, cols = x, picdat (rows, cols..

double function_value (double x);

int main(int argc, char *argv[]){
    int start_seed;
    int start, end, range;
    int num_iterations;
    int i;
    double x, y, max, min, rangey;
    double in, total;
    
    if (argc != 5){
        fprintf (stderr, "usage is: %s start end start_seed num_iterations\n", argv[0]);
        exit (1);
    }
    
    start_seed = atoi (argv [3]);
    srand (start_seed);
    
    start = atoi (argv [1]);
    end = atoi (argv [2]);
    range = end - start;
    num_iterations = atoi (argv [4]);
    max = 0;
    min = 0;
    in = 0;
    total = 0;
    
    for (i = 0; i < num_iterations; i++){
        x = ((double)rand ()/RAND_MAX * range) + start;
        if (function_value(x) > max) max = function_value(x);
        if (function_value(x) < min) min = function_value(x);
    }
    
    rangey = max - min;
    fprintf (stderr, "max = %lf  min = %lf  rangey = %lf\n", max, min, rangey);
    
    for (i = 0; i < num_iterations; i++){
        x = ((double)rand ()/RAND_MAX * range) + start;
        y = ((double)rand ()/RAND_MAX * rangey) + min;
        if (y < function_value (x)) in ++;
        total ++;
        fprintf (stderr, "x = %lf   y = %lf   value = %lf\n", x, y, function_value(x));
    }
    
    fprintf (stderr, "in = %lf   total = %lf\n", in, total);
    fprintf (stderr, "integral is %lf\n", in/total * max * range);
    
}

double function_value (double x){
    return sqrt (x) * log(x) * sqrt (cos (x) * cos(x));
}
