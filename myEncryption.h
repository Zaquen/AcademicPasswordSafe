/*********************************************************************
* Encryption Module Header File
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
#ifndef MY_ENCRYPTION_H
#define MY_ENCRYPTION_H

#include <string>

/**********************************************************************
 * Normalize Key
 * Takes length of a string to en/decrypt and the key, repeats the
 * key to match the length of the string.
 * Accepts the key, and length of the encryption string
 **********************************************************************/
void normalizeKey(std::string & key, const int length);

/********************************************************************
 * Read File
 * Open a file, return the string inside
 * Accepts a filename
 ********************************************************************/
std::string readFile(const std::string & file);

/********************************************************************
 * Write File
 * Overwrite the file with the new data
 * accepts the data string, and filename
 ********************************************************************/
void writeFile(const std::string & data, const std::string & file);

/********************************************************************
 * Encrypt
 * Function to encrypt a given file, using a modded Vigenere Cipher
 * Accepts a key and a filename
 ********************************************************************/
void encrypt(std::string key, const std::string & file);

/********************************************************************
 * Decrypt
 * Function to Decrypt a given file, using a modded Vigenere Cipher
 * Accepts a key and a filename
 ********************************************************************/
void decrypt(std::string key, const std::string file);

#endif /* MY_ENCRYPTION_H */