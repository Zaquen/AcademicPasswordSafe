/*********************************************************************
* Authentication Module
*
* Zaq Nelson
* 
* A simple Authentication implementation for my own library's sake
* Original implementation for use in Password Safe
*
* This mimics what would happen between a client and server,
* it is provided here as an extensible start to actual production
* For now, the master password is stored in a hard-coded file
* location, but will be more secure in a database.
*
* In mimicing what happens between Client and Server, any file 
* manipulation for the master password also occurs here.
*
* Technically, this information should be salted and hashed,
* but is beyond the scope of what I wanted to do here.
*
**********************************************************************/
#include "myAuthentication.h" // Header File
#include "myEncryption.h"     // For Encryption
#include <fstream>            // For Files
#include <iostream>           // For Debugging, Testing
#include <string>             // For Strings

#define FILENAME "authenticate.txt" // Hardcoded to mimic client/server

/* *************************************************************
* This struct is necessary because sensitive information needs
* to be encrypted even if the code is aborted in any way.
* wrapping the decryption process in a struct guarantees
* that the file will be reencrypted no matter what.
****************************************************************/
struct encryptionWrapper
{
    // The key is hardcoded here, because
    // it mimics the server login. This would
    // be stored securely on a server instead
    // of in the code
    std::string key = "ServerPassword";

    // Key is defined when authentication is prepared
    // The constructor needs to decrypt the file
    // to avoid any bugs or security breaches
    encryptionWrapper() { decrypt(key, FILENAME); }

    // If stopped for any reason, needs to encrypt!
    ~encryptionWrapper() { encrypt(key, FILENAME); }
};


/*******************************************************
 * Authenticate
 * Returns a True or a False depending if the password
 * matches what is stored in the "database" (just a file)
 * Accepts the password, since the username is not
 * necessary at this scale.
 *******************************************************/
const bool authenticate(std::string & password)
{
    // Decryption, wrapped in a Struct for security
    encryptionWrapper auth;

    // Read the info from file, store it in a string
    // ReadFile comes from myEncryption.h
    std::string fileText = readFile(FILENAME);

    // Return a boolean for a match or not
    return password == fileText;
}

/**********************************************************
 * Update Password
 * Changes the Master password. Must go through
 * Authentication first. Returns a Success or a Failure for
 * authentication.
 * Accepts the new and old password
 **********************************************************/
bool updatePassword(std::string & newPass, std::string & oldPass)
{
    // The user is attempting to change the password
    // This can fail
    // Wrong password case
    if (!authenticate(oldPass))
        return false;

    // Authentication is completed, may update the password
    // WriteFile comes from myEncryption.h
    // Make use of the encryption wrapper
    encryptionWrapper enc;
    writeFile(newPass, FILENAME);

    return true;
}



// Unimplemented for Debugging and Testing only
/*
int main()
{

    // Because C++ hates strings and char arrays
    std::string masterPass = "MasterPass";
    std::string masterPassword = "MasterPassword";

    // Remake the authenticate.txt file
    // and encrypt
    writeFile(masterPassword, FILENAME);
    encrypt("ServerPassword", FILENAME);

    // Test for initial authentication of correct password
    // Should print 'True'
    std::cout << "Authenticate Correct Password (1): ";
    std::cout << authenticate(masterPassword) << "\n";
    
    // Test for wrong password, should print false
    std::cout << "Authenticate Wrong Password (0): ";
    std::cout << authenticate(masterPass) << "\n";
    
    // Change the password to "MasterPass" incorrectly
    // Should print false
    std::cout << "Change Correct Password (0): ";
    std::cout << updatePassword(masterPass, masterPass) << "\n";

    // Change the password to "MasterPass" correctly
    // Should print true
    std::cout << "Change Correct Password (1): ";
    std::cout << updatePassword(masterPass, masterPassword) << "\n";

    // Change the password back to MasterPassword
    std::cout << "Back to original password (1): ";
    std::cout << updatePassword(masterPassword, masterPass) << "\n";
}
*/