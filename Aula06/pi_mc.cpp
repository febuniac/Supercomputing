/*

NAME:
   Pi_mc:  PI Monte Carlo

Purpose:
   This program uses a Monte Carlo algorithm to compute PI as an
   example of how random number generators are used to solve problems.
   Note that if your goal is to find digits of pi, there are much 
   better algorithms you could use.

Usage:
   To keep the program as simple as possible, you must edit the file
   and change the value of num_trials to change the number of samples
   used.  Then compile and run the program.

Algorithm:
   The basic idea behind the algorithm is easy to visualize.  Draw a 
   square on a wall.  Inside the square, draw a circle.  Now randomly throw 
   darts at the wall.  some darts will land inside the square.  Of those, 
   some will fall inside the circle.   The probability of landing inside
   the circle or the square is proportional to their areas.

   We can use a random number generator to "throw the darts" and count
   how many "darts" fall inside the square and how many inside the 
   cicle.  Dividing these two numbers gives us the ratio of their areas
   and from that we can compute pi.

Algorithm details:
   To turn this into code, I need a bit more detail.  Assume the circle
   is centered inside the square.  the circle will have a radius of r and 
   each side of the square will be of area 2*r (i.e. the diameter of the
   circle).  

       A(circle) = pi * r^2
       A(square) = (2*r)*(2*r) = 4*r^2

       ratio = A(circle)/A(square) = pi/4

   Since the probability (P) of a dart falling inside a figure (i.e. the square 
   or the circle) is proportional to the area, we have

       ratio = P(circle)/P(square) = pi/4

   If I throw N darts as computed by random numbers evenly distributed 
   over the area of the square

      P(sqaure) = N/N    .... i.e. every dart lands in the square
      P(circle) = N(circle)/N

      ratio = (N(circle)/N)/(N/N)  = N(circle)/N

   Hence, to find the area, I compute N random "darts" and count how many fall
   inside the circle.  The equation for a circle is

      x^2 + y^2 = r^2 

   So I randomly compute "x" and "y" evenly distributed from -r to r and 
   count the "dart" as falling inside the cicle if

      x^2 + y^2 < or = r

Results:  
   Remember, our goal is to demonstrate a simple monte carlo algorithm, 
   not compute pi.  But just for the record, here are some results (Intel 
   compiler version 10.0, Windows XP, core duo laptop)

       100        3.160000
       1000       3.148000
       10000      3.154000
       100000     3.139920
       1000000    3.141456
       10000000   3.141590
       100000000  3.141581

   As a point of reference, the first 7 digits of the true value of pi 
   is 3.141592 


History: 
   Written by Tim Mattson, 9/2007.

*/
#include <stdio.h>
#include <omp.h>
#include "random.h"
#include <vector>
#include <iostream>

// 
// The monte carlo pi program
//

static long num_trials = 100000000;
double mc(long num_trials){
    static long MULTIPLIER[] = {914334,360889,380985,283741,92717,43165,17364,219};
    static long PMOD[] = {4194301,2097143,1048573,524287,262139,131071,65521};
    long ADDEND=0;
    
    long i;  long Ncirc = 0;
    double pi, x, y, test;
    double r = 1.0;   // radius of circle. Side of squrare is 2*r 
     //seed(-r, r);  // The circle and square are centered at the origin
   //double time = omp_get_wtime();
      
   #pragma omp parallel//1 thread para core com uma copia do c'odigo que esta dentro
   { 
        long var =0;
        int tid = omp_get_thread_num();
        std::cout<<tid;
        Randz w( MULTIPLIER[tid], ADDEND,  PMOD[tid]);
        w.seed(-r, r);
        for(long i=0;i<num_trials/omp_get_num_threads(); i++){
            x = w.drandom();
            y = w.drandom();
            // test = x*x + y*y;
            if (x*x + y*y <= r*r){
                var+=1;
            }
    }
   #pragma omp critical
    Ncirc+=var;
   }
    pi = 4.0 * ((double)Ncirc/(double)num_trials);

    printf("\n %ld trials, pi is %lf ",num_trials, pi);
    //\printf(" in %lf seconds\n",omp_get_wtime()-time);
}
int main ()
{
    double time = omp_get_wtime();
    mc(num_trials);
    printf(" in %lf seconds\n",omp_get_wtime()-time);
 
    return 0;
}
	  
