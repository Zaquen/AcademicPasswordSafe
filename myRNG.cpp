/*********************************************************************
* RNG Module
*
* Zaq Nelson
* 
* A simple PRNG implementation for my own library's sake
* Statistically viable, but very deterministic
* Original implementation for use in Password Safe
*
**********************************************************************/
#include "myRNG.h"   // Header File
#include <iostream>  // for debugging
#include <cassert>   // for paranoia
#include "process.h" // for getpid()

/*********************************************************************
* RNG
* Returns a pseudo-random number between a minimum and maximum
* non-negative integer, inclusive
**********************************************************************/
int RNG(const int minimum, const int maximum)
{
    // Ensure the logic will work
    assert(minimum > -1);
    assert(minimum < maximum);

    // Get a random seed number from current process id
    // This will seed new numbers, MUST BE ODD
    static int seed = (_getpid() / 2) + 1;

    // I am using the Lehmer RNG algorithm
    // Thus, the seed needs to be odd, 
    // m must be a HIGH mersenne prime
    // and a must be the primitive root mod n
    // the calculation is Xnew = a X mod m
    // The following satisfy the requirements, with high period

    static int a = 16807;
    static int m = 2147483647;
    seed = a * (seed % m); 

    // Ensure the seed is non-negative
    if (seed < 0)
        seed *= -1;
    int num = seed;

    // This algorithm guarantees the new number is inside the min and max
    // by determining the spread and using the modulo operator
    // to keep it in that spread. Then, it adds the minimum number
    // to get in proper range.
    int spread = maximum - minimum;
    spread++;
    num = num % spread;
    num += minimum;

    // One statistically viable random number
    return num;
}

// Unimplemented, meant for debugging and testing
/*
int main()
{
    int count [10];
    for(int i = 0; i < 10; i++)
        count[i] = 0;

    int data;
    for(int i = 0 ; i < 100; i++)
    {
        data = RNG(5, 9);
        count[data]++;
    }       

    for(int i = 0; i < 10; i++)
        std::cout << i << ": " << count[i] << "\n";
}
*/