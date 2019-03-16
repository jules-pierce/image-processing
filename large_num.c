
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

double getN01 ();
double getU01 ();

int main(int argc, char *argv[] ){
    int num_values;
    int i, j;
    double y, sum;
    unsigned int start_seed;
    
    if (argc != 5){
        fprintf (stderr, "usage is: %s start_seed distribution_type num_values y_value\n", argv [0]);
        exit (1);
    }
    
    num_values = atoi (argv [3]);
    start_seed = atoi (argv[1]);
    srand (start_seed);
    sum = 1/100;
    
    for (i = 0; i < num_values; i++){
        y = getU01();
        sum += y;
        printf ("%5d   %5lf\n", i+1, sum/(i+1));
    }

    
}

/*double getN01 (){
    static double y2;
    double y1, x1, x2;
    static int first_call = 1;
    
    if (first_call == 1){
        x1 = getU01 ();
        x2 = getU01 ();
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
    
}*/

double getU01 (){
    double x1;
    
    x1 = (double)(rand())/RAND_MAX;
    //printf("x = %lf\n", x1);
    return x1;
}

