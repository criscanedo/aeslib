#include <string>
#include <crypto/secblock.h>
#include "cipher.h"

std::string Cipher::encrypt(std::string plaintext)
{
    return "";
}

std::string Cipher::decrypt(std::string ciphertext)
{
    return "";
}

void Cipher::setKey(std::string key)
{
    d_key(reinterpret_cast<const byte*>(&key[0]), key.size());
}

void Cipher::setIV(std::string iv)
{
    d_iv(reinterpret_cast<const byte*>(&iv[0]), iv.size());
}
