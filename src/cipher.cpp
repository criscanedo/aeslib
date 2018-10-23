#include <string>
#include <crypto/cryptlib.h>
#include <crypto/osrng.h>
#include <crypto/aes.h>
#include <crypto/filters.h>
#include <crypto/modes.h>
#include <crypto/secblock.h>
#include "cipher.h"

using CryptoPP::AES;
using CryptoPP::BufferedTransformation;
using CryptoPP::CBC_MODE;
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::SecByteBlock;

static int Cipher::_ivSize = 0x10;
static CryptoPP::AutoSeededRandomPool Cipher::s_rand;
static bool Cipher::s_isKeySet = false;

std::string Cipher::encrypt(std::string plaintext)
{
    if (!s_isKeySet) {
        throw std::runtime_error("Key has not been set.");
    }

    std::string ciphertext, ivPlaintext;

    ivPlaintext = ivToPlaintext(d_iv);
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

std::string Cipher::ivtp(CryptoPP::SecByteBlock iv)
{
    if (iv.size() < _ivSize) {
        throw std::runtime_error("iv: Not a valid IV size for AES.");
    }

    return std::string(reinterpret_cast<const char*>(&iv[0]), iv.size());
}

SecByteBlock Cipher::generateIV()
{
    s_rand.GenerateBlock(d_iv);
    return d_iv;
}

std::string Cipher::decrypt(std::string ciphertext)
{
    if (!s_isKeySet) generateKey();

    std::string plaintext, ivPlaintext;

    ivPlaintext = extractIV(ciphertext);
    setIV(ivPlaintext);

    ciphertext = ciphertext.substr(AES::BLOCKSIZE);

    try {
        CBC_MODE<AES>::Decryption blockCipher;
        blockCipher.setKeyWithIv(d_key, d_key.size(), d_iv);

        StringSource ss(ciphertext, true,
                        new StreamTransformationFilter(blockCipher,
                        new StringSink(plaintext)));
        return plaintext;
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
    s_isKeySet = true;
    return d_key;
}

bool Cipher::setKey(std::string key)
{
    if (!s_isKeySet) {
        d_key = SecByteBlock(reinterpret_cast<const CryptoPP::byte*>(&key[0]), key.size());
        s_isKeySet = true;
        return true;
    }
    return false;
}

void Cipher::setIV(std::string iv)
{
    d_iv = SecByteBlock(reinterpret_cast<const CryptoPP::byte*>(&iv[0]), iv.size());
}

std::string Cipher::encode64(std::string text)
{
    return "";
}

std::string Cipher::decode64(std::string text)
{
    return "";
}
