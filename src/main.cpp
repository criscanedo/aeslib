#include <iostream>
#include <string>
#include "cipher.h"
using std::string;

int main()
{
    string plaintext, ciphertext, encoded, decoded;
    string key;

    std::cout << "Enter the plaintext to encrypt: ";
    std::cin >> plaintext;

    std::cout << "Enter key to encrypt/decrypt with: ";
    std::cin >> key;

    Cipher::setKey(key);
    Cipher::generateIV();

    ciphertext = Cipher::encrypt(plaintext);
    std::cout << "\nCiphertext: " << ciphertext << std::endl;

    encoded = Cipher::encode64(ciphertext);
    std::cout << "\nEncoded: " << encoded << std::endl;

    decoded = Cipher::decode64(encoded);
    std::cout << "\nDecoded: " << decoded << std::endl;

    ciphertext = Cipher::decrypt(ciphertext);
    std::cout << "\nDecrypted: " << ciphertext << std::endl;

    return 0;
}
