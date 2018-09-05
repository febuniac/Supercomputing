
//**********************************************************
// Pseudo random number generator:
//     double random
//     void seed (lower_limit, higher_limit)
//**********************************************************
//
// A simple linear congruential random number generator
// (Numerical Recipies chapter 7, 1st ed.) with parameters
// from the table on page 198j.
//
//  Uses a linear congruential generator to return a value between
//  0 and 1, then scales and shifts it to fill the desired range.  This
//  range is set when the random number generator seed is called.
// 
// USAGE:
//
//      pseudo random sequence is seeded with a range
//
//            void seed(lower_limit, higher_limit)
//   
//      and then subsequent calls to the random number generator generates values
//      in the sequence:
//
//            double drandom()
//
// History: 
//      Written by Tim Mattson, 9/2007.
//      changed to drandom() to avoid collision with standard libraries, 11/2011


#include "random.h"

Randz::Randz(long MULTIPLIER,long ADDEND, long PMOD) :
    MULTIPLIER(MULTIPLIER),
    ADDEND(ADDEND),
    PMOD(PMOD){
}


double Randz::drandom()
{
    long random_next;
    double ret_val;
// 
// compute an integer random number from zero to mod
//
    random_next = (MULTIPLIER  * random_last + ADDEND)% PMOD;
    random_last = random_next;

//
// shift into preset range
//
    ret_val = ((double)random_next/(double)PMOD)*(random_hi-random_low)+random_low;
    return ret_val;
}
//
// set the seed and the range
//
void Randz::seed(double low_in, double hi_in)
{
   if(low_in < hi_in)
   { 
      random_low = low_in;
      random_hi  = hi_in;
   }
   else
   {
      random_low = hi_in;
      random_hi  = low_in;
   }
   random_last = PMOD/ADDEND;  // just pick something

}
//**********************************************************
// end of pseudo random generator code.
//**********************************************************
