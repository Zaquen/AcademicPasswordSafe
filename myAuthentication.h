/*********************************************************************
* Authentication Module Header File
*
* Zaq Nelson
* 
* A simple Authentication implementation for my own library's sake
* Original implementation for use in Password Safe
*
**********************************************************************/
#ifndef MY_AUTHENTICATION_H
#define MY_AUTHENTICATION_H

#include <string>

/*******************************************************
 * Authenticate
 * Returns a True or a False depending if the password
 * matches what is stored in the "database" (just a file)
 * Accepts the password, since the username is not
 * necessary at this scale.
 *******************************************************/
const bool authenticate(std::string & password);

/**********************************************************
 * Update Password
 * Changes the Master password. Must go through
 * Authentication first. Returns a Success or a Failure for
 * authentication.
 * Accepts the new and old password
 **********************************************************/
bool updatePassword(std::string & newPass, std::string & oldPass);

#endif /* MY_AUTHENTICATION_H */