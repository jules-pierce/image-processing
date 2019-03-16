//
//  test4.c
//  
//
//  Created by Jules Pierce on 7/7/15.
//
//

#include <stdio.h>

typedef enum {RED, GREEN, BLUE} p_color_t;

void changemyarg (int *r);

int main (int argc, char *argv[]){
    p_color_t jules;
    int r;
    
    jules = 0;
    if (jules == RED){
        printf ("I'm red %d\n", jules);
    }
    changemyarg (&r);
    printf ("%d\n", r);
}

void changemyarg (int *r){
    *r = 50;
    return;
}