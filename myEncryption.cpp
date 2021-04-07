/*********************************************************************
* Encryption Module
*
* Zaq Nelson
* 
* A simple Encryption implementation for my own library's sake
* This will encrypt and decrypt an entire file
* The algorithm is a modified Vigenere Cipher
*
* NOTE*** Please do not use this for anything actually secure
* This is simply an academic exercise to practice cryptography
*
* Any en/decryption that happens WILL overwrite the file. Take
* caution as there is no recovery built in here
*
* Original implementation for use in Password Safe
**********************************************************************/
#include "myEncryption.h" // Header File
#include <fstream>  // For Files
#include <string>   // For strings and getline
#include <iostream> // For Errors

/**********************************************************************
 * Normalize Key
 * Takes length of a string to en/decrypt and the key, repeats the
 * key to match the length of the string.
 * Accepts the key, and length of the encryption string
 **********************************************************************/
void normalizeKey(std::string & key, const int length)
{
    // A temp variable for repeating purposes
    std::string keyRepeat = key;

    // Add the repeating key until it is at least as big as what is
    // being encrypted
    while (key.length() < length)
        key += keyRepeat;

    // Scrape off any excess
    key.erase(length);
}

/********************************************************************
 * Read File
 * Open a file, return the string inside
 * Accepts a filename
 ********************************************************************/
std::string readFile(const std::string & file)
{
    // Return String including the file
    std::string data;

    // Get Line string
    std::string line;

    // Wrap the file items in a try-catch block in case there 
    // is a problem
    try
    {
        // Open the file and read the contents
        std::ifstream myFile;
        myFile.open(file);
        while(!myFile.eof())
        {
            std::getline(myFile, line);
            data += line + "\n";
        }
        // Take care of the extra endline
        data.erase(data.length() - 1);
        myFile.close();
    }

    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }

    // Return the contents of the file
    return data;
}

/********************************************************************
 * Write File
 * Overwrite the file with the new data
 * accepts the data string, and filename
 ********************************************************************/
void writeFile(const std::string & data, const std::string & file)
{
    // Wrap the file items in a try-catch block in case there 
    // is a problem
    try
    {
        // Open the file
        std::ofstream myFile;
        myFile.open(file, std::ofstream::trunc);
        // trunc erases the data in the file, fresh to be overwritten

        // Write the data and close
        for(int i = 0; i < data.length(); i++)
            myFile << data[i];
        myFile.close();
    }

    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

/********************************************************************
 * Encrypt
 * Function to encrypt a given file, using a modded Vigenere Cipher
 * Accepts a key and a filename
 ********************************************************************/
void encrypt(std::string key, const std::string & file)
{
    // Put the file contents into a string, prepare key
    std::string data;
    data = readFile(file);
    normalizeKey(key, data.length());

    // Encrypt the data according to a modded Vigenere Cipher:
    // Add the char value from a repeating part of a key
    // to the original value, encrypting it.
    for(int i = 0; i < data.length(); i++)
        data[i] += key[i];

    // Write the encrypted data back into the file
    writeFile(data, file);
}

/********************************************************************
 * Decrypt
 * Function to Decrypt a given file, using a modded Vigenere Cipher
 * Accepts a key and a filename
 ********************************************************************/
void decrypt(std::string key, const std::string file)
{
    // Put the file contents into a string, prepare key
    std::string data;
    data = readFile(file);
    normalizeKey(key, data.length());

    // Decrypt the data according to a modded Vigenere Cipher:
    // Sub the char value from a repeating part of a key
    // to the original value, decrypting it.
    for(int i = 0; i < data.length(); i++)
        data[i] -= key[i];

    // Write the Decrypted data back into the file
    writeFile(data, file);
}

// Unimplemented, meant for Debugging and Testing
/*
int main()
{
    // Setup the test variables, key and file
    std::string key = "IamAwesome";
    std::string file = "test.txt";

    // Prepare the test file and print results
    writeFile("This\nshould work", file);
    std::cout << "Written:\n" << readFile(file) << "\n";

    // Run the encryption and print results
    encrypt(key, file);
    std::cout << "Encrypted:\n" << readFile(file) << "\n";

    // Run the decryption and print results
    decrypt(key, file);
    std::cout << "Decrypted:\n" << readFile(file) << "\n";

    return 0;
}
*/