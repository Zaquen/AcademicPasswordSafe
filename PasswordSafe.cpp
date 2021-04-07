/*********************************************************************
* Password Safe
*
* Zaq Nelson
* 
* A simple Password Safe for my own purposes.
*
* This handles all of the communication between the GUI
* and the C++ implementations
*
**********************************************************************/

#include "myEncryption.h"         // For encryption
#include "myRNG.h"                // For PRNG numbers
#include "myAuthentication.h"     // For Authentication
#include <string>                 // For Strings
#include <iostream>               // For Debugging

#define FILENAME "logins.txt"     // Logins stored here

/**************************************************************
 * MAIN
 * The GUI will send requests based on the arguments provided
 * a code will always be a part of it to know the request
 ***************************************************************/
int main(int argc, char **argv)
{
    /*
    Code 0: Decrypt login information, comes with a string for auth
            Also just logs in to the platform
    Code 1: Update master password, comes with 2 strings
    Code 2: Encrypt the file, comes with key
    Code 3: Generate a random salt for a login (for extensibility)
    Code 4: 
    return 0 If access was denied
    return 1 If access was approved
    */

    std::string masterPassword = argv[2];
    std::string newPassword; // Only assigned if exists
    if (argc == 4)
        newPassword = argv[3];

    int code; // Var for switch
    sscanf (argv[1],"%d",&code); // cast to int for switch

    // Debugging
    std::cout << code;

    switch (code)
    {
        case 0:
            if(authenticate(masterPassword)) // Authenticate Master Password
            {
                decrypt(masterPassword, FILENAME);
                return 1;
            }
            else
                return 0;
            break;
        case 1:
            if(updatePassword(newPassword, masterPassword)) // Update the password
            {
                return 1;
            }
            else    
                return 0;
            break;
        case 2:
            encrypt(masterPassword, FILENAME); // Called at termination of GUI
            break;
       case 3: // Generate a random salt!
            return RNG(100, 1000);
       default:
            break;
    }
}