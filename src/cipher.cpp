#include <string>
#include <crypto/secblock.h>
#include "cipher.h"

std::string Cipher::encrypt(std::string plaintext)
{
    std::string ciphertext, ivPlaintext;
    return "";
}

std::string Cipher::decrypt(std::string ciphertext)
{
    return "";
}

void Cipher::setKey(std::string key)
{
    d_key = CryptoPP::SecByteBlock(reinterpret_cast<const CryptoPP::byte*>(&key[0]), key.size());
}

void Cipher::setIV(std::string iv)
{
    d_iv = CryptoPP::SecByteBlock(reinterpret_cast<const CryptoPP::byte*>(&iv[0]), iv.size());
}

std::string Cipher::getIVPlaintext()
{
    return std::string(reinterpret_cast<const char*>(&d_iv[0]), d_iv.size());
}
