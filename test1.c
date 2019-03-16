#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "bmp_io.h"
#include "imgstuff.h"
#include "CN.h"


int main (int argc, char *argv[]){
    CN_t x, y, z;
    int n;

    x.re = 6;
    x.im = 3;

    y.re = 10;
    y.im = 5;

    n = 3;

		printf("x.re = %10.4lf  x.im = %10.4lf\n", x.re, x.im);
		printf("y.re = %10.4lf  y.im = %10.4lf\n", y.re, y.im);
		printf("n = %d\n\n\n", n);
		
    z = CN_mult (x,y);
		printf("mult(x,y) z.re = %10.4lf  z.im = %10.4lf\n", z.re, z.im);

    z = CN_add (y, x);
		printf("add(x,y) z.re = %10.4lf  z.im = %10.4lf\n", z.re, z.im);

    z = CN_subtract (y, x);
		printf("sub(y,x) z.re = %10.4lf  z.im = %10.4lf\n", z.re, z.im);

    z = CN_pow (x, n);
		printf("pow(x) z.re = %10.4lf  z.im = %10.4lf\n", z.re, z.im);

		printf("mag(x)  mag of x = %10.4lf\n", CN_mag(x) );

}
