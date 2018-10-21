#include <iostream>
#include <string>
#include <crypto/cryptlib.h>
#include <crypto/osrng.h>
#include <crypto/secblock.h>
#include <crypto/base64.h>
#include <crypto/filters.h>
#include <crypto/modes.h>
#include <crypto/aes.h>
using std::string;

typedef unsigned char byte;

string encrypt(string plaintext, string ekey, byte* eiv);
string decrypt(string ciphertext, string ekey);

int main()
{
    string plaintext;

    std::cout << "Enter the plaintext to encrypt: ";
    std::cin >> plaintext;

    CryptoPP::AutoSeededRandomPool rnd;

    CryptoPP::SecByteBlock key(0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
    byte iv[CryptoPP::AES::BLOCKSIZE];

    std::cout << "Size of iv array: " << sizeof(iv) << std::endl;

    rnd.GenerateBlock(key, key.size());
    rnd.GenerateBlock(iv, sizeof(iv));

    //string ciphertext = encrypt(plaintext, key, iv);
    //Encode here first
    //std::cout << "Encrypted text: " << ciphertext << std::endl;

    //string roundtrip = decrypt(ciphertext, key);
    //std::cout << "Decrypted text: " << roundtrip << std::endl;

    return 0;
}
/*
string encrypt(string plaintext, string ekey, byte* eiv)
{
    string ciphertext, ivplaintext;
    SecByteBlock key(reinterpret_cast<const byte*>(&ekey[0]), ekey.size());
    SecByteBlock iv(eiv, eiv.size());
    ivplaintext = std::string(reinterpret_cast<const char*>(&iv[0]), iv.size());
    
    // Prepend unencrypted IV to cipher before encryption
    ciphertext = ivplaintext;

    try {
        CBC_MODE<AES>::Encryption blockCipher;
        blockCipher.setKeyWithIv(key, key.size(), iv);

        CryptoPP::StringSource ss(plaintext, true, new StreamTransformationFilter(blockCipher, new StringSink(ciphertext)));
        return ciphertext;
    }
    catch(const CryptoPP::Exception& e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

string decrypt(string ciphertext, string ekey)
{
    string plaintext, ivplaintext;

    // Copy first 16 bytes from ciphertext
    ivplaintext = ciphertext.substr(0, AES::BLOCKSIZE);

    // Remove IV from ciphertext
    ciphertext = ciphertext.substr(AES::BLOCKSIZE);

    try {
        SecByteBlock key(reinterpret_cast<const byte*>(&ekey[0]), ekey.size());
        SecByteBlock iv(reinterpret_cast<const byte*>(&ivplaintext[0]), ivplaintext.size());
        CBC_MODE<AES>::Decryption blockCipher;
        blockCipher.setKeyWithIv(key, key.size(), iv);

        CryptoPP::StringSource ss(ciphertext, true, new StreamTransformationFilter(blockCipher, new StringSink(plaintext)));
        return plaintext;
    }
    catch(const CryptoPP::Exception& e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
} */
