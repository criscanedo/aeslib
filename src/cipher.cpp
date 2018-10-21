#include <string>
#include <crypto/cryptlib.h>
#include <crypto/osrng.h>
#include <crypto/aes.h>
#include <crypto/filters.h>
#include <crypto/modes.h>
#include <crypto/secblock.h>
#include <memory>
#include "cipher.h"

using CryptoPP::AES;
using CryptoPP::BufferedTransformation;
using CryptoPP::CBC_MODE;
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::SecByteBlock;

static CryptoPP::AutoSeededRandomPool s_rand;

std::string Cipher::encrypt(std::string plaintext)
{
    std::string ciphertext, ivPlaintext;

    ivPlaintext = ivToPlaintext();
    ciphertext = ivplaintext;

    try {
        CBC_MODE<AES>::Encryption blockCipher;
        blockCipher.setKeyWithIv(d_key, d_key.size(), d_iv);

        StringSource ss(plaintext, true,
                        new StreamTransformationFilter(blockCipher,
                        new StringSink(ciphertext)));

        return ciphertext;
    }
    catch(const CryptoPP::Exception& e) {
        throw e;
    }
}

std::string Cipher::ivToPlaintext(CryptoPP::SecByteBlock iv)
{
    if (iv.size() == 0 && d_iv.size() == 0) {
        generateIV();
    }
    else if (iv.size() != 0) {
        d_iv = iv;
    }

    return std::string(reinterpret_cast<const char*>(&d_iv[0]), d_iv.size());
}

SecByteBlock Cipher::generateIV()
{
    s_rand.GenerateBlock(d_iv);
    return d_iv;
}

std::string Cipher::decrypt(std::string ciphertext)
{
    std::string plaintext, ivPlaintext;

    ivPlaintext =     setIV(ivPlaintext);
    setIV(ivPlaintext);

    ciphertext = ciphertext.substr(AES::BLOCKSIZE);

    try {
        CBC_MODE<AES>::Decryption blockCipher;
        blockCipher.setKeyWithIv(d_key, d_key.size(), d_iv);

        stringSink = createStringSink(plaintext);
        streamTransFilter = createStreamTransFilter(blockCipher);

        StringSource ss(ciphertext, 
    }
    catch(const CryptoPP::Exception& e) {
        throw e;
    }
}

std::string Cipher::extractIV(std::string ciphertext)
{
    return ciphertext.substr(AES::BLOCKSIZE);
}

SecByteBlock Cipher::generateKey()
{
    s_rand.GenerateBlock(d_key);
    return d_key;
}

void Cipher::setKey(std::string key)
{
    d_key = SecByteBlock(reinterpret_cast<const CryptoPP::byte*>(&key[0]), key.size());
}

void Cipher::setIV(std::string iv)
{
    d_iv = SecByteBlock(reinterpret_cast<const CryptoPP::byte*>(&iv[0]), iv.size());
}

