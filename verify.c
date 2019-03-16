#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "imgstuff.h"

int factorial (int n);

int main(int argc, char *argv[]){
    int i, l;
    double n;
    double sum = 0;
    
    if (argc != 4){
        fprintf (stderr, "usage is: %s type (cos,sin, e) number iterations\n", argv [0]);
        exit (1);
    }
    
    n = atof (argv [2]);
    l = atoi (argv [3]) / 2;
    
    //printf ("%s\n", argv[1]);
    
    if (strcmp (argv [1], "cos")==0){
        //printf ("testing cos\n");
        for (i = 1; i < l; i++){
            //printf ("%lf\n", pow (-1, i) * pow (n, 2*i) / factorial (2*i));
            sum += pow (-1, i) * pow (n, 2*i) / factorial (2*i);
        }
        printf ("cos of %lf is %lf    mathlib returns: %lf\n", n, 1 + sum, cos(n));
    }
    
    else if (strcmp(argv [1], "sin")==0){
        for (i = 1; i < l; i++){
            sum += pow (-1, i+1) * pow (n, 2*i + 1) / factorial (2*i + 1);
        }
        printf ("sin of %lf is %lf    mathlib returns: %lf\n", n, n - sum, sin(n));
    }
             
    else if (strcmp(argv [1], "e")==0){
        for (i = 1; i < 2*l; i++){
            sum += pow (n, i) / factorial (i);
        }
        printf ("e to the power of %lf is %lf     mathlib returns: %lf\n", n, sum + 1, exp(n));
    }
    
    else {
        printf ("Invalid input");
        exit (1);
    }
    
    
}

int factorial (int n){
    int i, sum;
    sum = 1;
    
    for (i = 1; i <= n; i++){
        sum *= i;
    }
    
    //printf ("factorial is %d\n", sum);
    return sum;
}
