#include "prog.h"


/* Function returns the nth term in the Fibinocci sequence through a recursive algorithm */
int nthFib(int n)
{
    /* Question 1: Implement function. */
    if (n < 1 || n > 30)  return -1;
    else if (n == 1)  return 0;
    else if (n == 2) return 1;
    else return nthFib(n-1) + nthFib(n-2);
}

int asq_minus_bsq(int a, int b)
{
    /* Question 2: Implement function. */
    return (a*a) - (b*b);
}

