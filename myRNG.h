/*********************************************************************
* RNG Module Header File
*
* Zaq Nelson
* 
* A simple PRNG implementation for my own library's sake
* Statistically viable, but very deterministic
* Original implementation for use in Password Safe
*
**********************************************************************/
#ifndef MY_RNG_H
#define MY_RNG_H
/*********************************************************************
* RNG
* Returns a pseudo-random number between a minimum and maximum
* non-negative integer, inclusive
**********************************************************************/
int RNG(const int minimum, const int maximum);

#endif /* MY_RNG_H */