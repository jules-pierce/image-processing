//
//  test3.c
//  
//
//  Created by Jules Pierce on 7/7/15.
//
//
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "imgstuff.h"
#include "bmp_io.h"

#define FPS 30.0

typedef struct puck{
    double x0; //old x
    double y0; //old y
    double x; //start x
    double y; //start y
    double vx; //x velocity
    double vy; //y velocity
    unsigned char r; //radius
}puck_t;

typedef struct accel{
    double x1;
    double y1;
    double x2;
    double y2;
    double v;
}accel_t;

void insert_object (unsigned char *picdat, puck_t p);
void prepare_pic (unsigned char *picdat, accel_t *a, int num_accel);
void check_accels (accel_t *a, puck_t *p, unsigned char *picdat);
void check_edge (puck_t* p, unsigned char *picdat);

int g_cols = 1280;
int g_rows = 720;


int main (int argc, char *argv[]){
    unsigned char *picdat;
    puck_t p;
    double T;
    FILE *in_fd;
    int i, j, k;
    double num_sec;
    int num_accel;
    accel_t *a;
    char filename [80];
    double vel_length;
    
    picdat = (unsigned char*) malloc (3 * g_rows * g_cols * sizeof (unsigned char));
    //printf ("check\n");
    
    if (argc != 3){
        printf ("usage is: %s num_sec output_name\n", argv [0]);
        exit (1);
    }
    
    T = 1.0 / FPS;
    num_sec = atof (argv [1]);
    in_fd = fopen ("air_hockey_info.txt", "r");
    fscanf (in_fd, "%lf %lf %lf %lf", &p.x0, &p.y0, &p.vx, &p.vy);
    printf ("x0 = %lf y0 = %lf vx= %lf vy = %lf\n", p.x0, p.y0, p.vx, p.vy);
    fscanf (in_fd, "%d", &num_accel);
    
    a = (accel_t*) malloc (num_accel * sizeof (accel_t));
    
    for (i = 0; i < num_accel; i++){
        fscanf (in_fd, "%lf %lf %lf %lf %lf", &a[i].x1, &a[i].y1, &a[i].x2, &a[i].y2, &a[i].v);
    }
    //printf ("here\n");
    
    vel_length = sqrt ( (p.vx * p.vx) + (p.vy * p.vy));

    for (i = 0; i < (int)(FPS * num_sec); i++){
        if (i % 10 == 0){
            printf ("processing frame = %d velocity vector = %lf\n", i, vel_length);
        }
        prepare_pic (picdat, a, num_accel);
        
        p.x = p.x0 + p.vx * T;
        p.y = p.y0 + p.vy * T;
        
        insert_object (picdat, p);
        
        //printf ("peace out girl scout\n");
        check_edge (&p, picdat);
        for (j = 0; j < num_accel; j++){
            check_accels (&a[j], &p, picdat);
        }
        //printf ("kitty\n");
        sprintf (filename, "%s%05d.bmp", argv[2], i);
        //printf ("ok\n");
        output_bmp (filename, g_cols, g_rows, picdat, RGB);
        //printf ("yup\n");
        p.x0 = p.x;
        p.y0 = p.y;
        vel_length = sqrt ( (p.vx * p.vx) + (p.vy * p.vy));
    }
    printf ("not dead yet\n");
    fclose (in_fd);
    free (picdat);
}

void insert_object (unsigned char *picdat, puck_t p){
    int i, j, k;
    double length;
    double x, y;
    int blur_count = 20;
    p.r = 10;
    
    for (k = 0; k <= blur_count; k++){
        x = p.x0 + k * (p.x - p.x0)/blur_count;
        y = p.y0 + k * (p.y - p.y0)/blur_count;
        for (i = y - p.r; i <= y + p.r; i++){
            for (j = x - p.r; j <= x + p.r; j++){
                if( i < 0 || i > g_rows - 1 ||
                   j < 0 || j > g_cols - 1) continue;
                length = sqrt( (double) ((i-y)*(i-y) + (j-x)*(j-x) ) );
                if (length <= p.r){
                    /*picdat [ri (i, j, g_cols)] = 55;
                    picdat [gi (i, j, g_cols)] = 92;
                    picdat [bi (i, j, g_cols)] = 74;*/
                    picdat [ri (i, j, g_cols)] = 0;
                    picdat [gi (i, j, g_cols)] = 255;
                    picdat [bi (i, j, g_cols)] = 0;
                }
            }
        }
    }
    return;
}

void prepare_pic (unsigned char *picdat, accel_t *a, int num_accel){
    int i, j, k;
    int slope;
    for (i = 0; i < g_rows; i++){
        for (j = 0; j < g_cols; j++){
            /*picdat [ri (i, j, g_cols)] = picdat [ri (i, j, g_cols)] * .5;
            picdat [gi (i, j, g_cols)] = picdat [gi (i, j, g_cols)] * .5;
            picdat [bi (i, j, g_cols)] = picdat [bi (i, j, g_cols)] * .5;*/
            picdat [ri (i, j, g_cols)] = 0;
            picdat [gi (i, j, g_cols)] = 0;
            picdat [bi (i, j, g_cols)] = 0;

            if( (i > 10 && i < 20) ||
                (j > 10 && j < 20) ||
                (i > g_rows - 20 && i < g_rows - 10) ||
                (j > g_cols - 20 && j < g_cols - 10) ){
                    picdat [ri (i, j, g_cols)] = 255;
                    picdat [gi (i, j, g_cols)] = 255;
                    picdat [bi (i, j, g_cols)] = 255;
            }
        }
    }
    
    for (k = 0; k < num_accel; k++){
        if ((a[k].x2 - a[k].x1) == 0) slope = 1000;
        else slope = (a[k].y2 - a[k].y1)/(a[k].x2 - a[k].x1);
    
        for (i = a[k].y1; i < a[k].y2; i++){
            for (j = a[k].x1; j < a[k].x2; j++){
                //printf ("%d\n", j);
                if (i == (slope * (j - a[k].x1)) + a[k].y1){
                    picdat [ri (i, j, g_cols)] = 224;
                    picdat [gi (i, j, g_cols)] = 102;
                    picdat [bi (i, j, g_cols)] = 254;
                    //printf ("coloring accelerator\n");

                    picdat [ri (i+1, j, g_cols)] = 224;
                    picdat [gi (i+1, j, g_cols)] = 102;
                    picdat [bi (i+1, j, g_cols)] = 254;
                    //printf ("coloring accelerator\n");

                    picdat [ri (i-1, j, g_cols)] = 224;
                    picdat [gi (i-1, j, g_cols)] = 102;
                    picdat [bi (i-1, j, g_cols)] = 254;
                    //printf ("coloring accelerator\n");
                }
            }
        }
    }

    return;
}

void check_accels(accel_t *a, puck_t *p, unsigned char *picdat){
    double slope1, slope2;
    double x, y;
    int i, j;
    int ax1, ax2, ay1, ay2, px0, px;
    //printf ("checking accelerator\n");
    if ((a->x2 - a->x1) == 0) slope1 = 1000;
    else slope1 = (a->y2 - a->y1)/(a->x2 - a->x1);
    if ((p->x - p->x0) == 0) slope2 = 1000;
    else slope2 = (p->y - p->y0)/ (p->x - p->x0);
    if (slope1 == slope2) return;
    x = ((slope1 * a->x1) - (slope2 * p->x) + p->y - a->y1)/ (slope1 - slope2);
    y = (slope1 * (x - a->x1)) + a->y1;
    //printf (" x = %lf y = %lf\n", x, y);
    if (a->x1 > a->x2){
        ax1 = a->x2;
        ax2 = a->x1;
    }
    else{
        ax1 = a->x1;
        ax2 = a->x2;
    }
    if (a->y1 > a->y2){
        ay1 = a->y2;
        ay2 = a->y1;
    }
    else{
        ay1 = a->y1;
        ay2 = a->y2;
    }
    /*
    if (p->x > p->x0){
        px = p->x;
        px0 = p->x0;
    }
    else{
        px = p->x0;
        px0 = p->x;
    }
     */
    //printf ("ax1 = %d ax2 = %d ay1 = %d ay2 = %d\n", ax1, ax2, ay1, ay2);
    //printf (" p.x0 = %lf p.y0 = %lf p.x = %lf p.y = %lf\n", p->x0, p->y0, p->x, p->y);
    if (x > ax1 && x < ax2 && y > ay1 && y < ay2){
        //printf ("halfway\n");
        //comparison isn't working-- never tests as true
        //printf ("px0 = %d x = %d px = %d\n", px0, x, px);
        if ( (p->x0 <= x && p->x >= x) &&
             ( (p->y0 <= y && p->y >= y ) || 
						   (p->y0 >= y && p->y <= y) ) ) {
            printf ("boosting speed\n");
            p->vx = (sqrt ((p->vx * p->vx) + (p->vy * p->vy)) * 1.5 ) * (cos (atan2 (p->vy, p->vx)));
            p->vy = (sqrt ((p->vx * p->vx) + (p->vy * p->vy)) * 1.5 ) * (sin (atan2 (p->vy, p->vx)));
            //printf ("velocity increased\n");
            return;
        }
        if ( (p->x0 >= x && p->x <= x) &&
                ( (p->y0 <= y && p->y >= y ) ||
                    (p->y0 >= y && p->y <= y) ) ) {
                printf ("lowering speed\n");
                p->vx = (sqrt ((p->vx * p->vx) + (p->vy * p->vy)) * 0.5 ) * (cos (atan2 (p->vy, p->vx)));
                p->vy = (sqrt ((p->vx * p->vx) + (p->vy * p->vy)) * 0.5 ) * (sin (atan2 (p->vy, p->vx)));
                //printf ("velocity increased\n");
                return;
            }
    }
}

#define MARG 35

void check_edge (puck_t* p, unsigned char *picdat){
    //check for edge
    int i, j;
		
    if (p->x < MARG || p->x > g_cols - MARG) {
        p->vx = -p->vx;
    }
    if (p->y < MARG || p->y > g_rows - MARG){
        p->vy = -p->vy;
    }

    return;
}

/*
 ideas:
 -print frame number and puck velocity or magnitude of velocity
 -decelerator
 */



