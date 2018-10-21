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
    std::unique_ptr<BufferedTransformation> streamTransFilter;
    std::unique_ptr<StringSink> stringSink;

    ivPlaintext = getIVPlaintext();
    ciphertext = ivplaintext;

    try {
        CBC_MODE<AES>::Encryption blockCipher;
        blockCipher.setKeyWithIv(d_key, d_key.size(), d_iv);

        streamTransFilter = createStreamTransFilter(blockCipher);
        stringSink = createStringSink(ciphertext);
        
        StringSource ss(plaintext, true, streamTransFilter, stringSink);
        return ciphertext;
    }
    catch(const CryptoPP::Exception& e) {
        throw e;
    }
}

std::string Cipher::decrypt(std::string ciphertext)
{
    std::string plaintext, ivPlaintext;
    std::unique_ptr<BufferedTransformation> streamTransFilter;
    std::unique_ptr<StringSink> stringSink;

    ivPlaintext = ciphertext.substr(0, AES::BLOCKSIZE);
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

SecByteBlock Cipher::generateKey()
{
    s_rand.GenerateBlock(d_key);
    return d_key;
}

SecByteBlock Cipher::generateIV()
{
    s_rand.GenerateBlock(d_iv);
    return d_iv;
}

void Cipher::setKey(std::string key)
{
    d_key = SecByteBlock(reinterpret_cast<const CryptoPP::byte*>(&key[0]), key.size());
}

void Cipher::setIV(std::string iv)
{
    d_iv = SecByteBlock(reinterpret_cast<const CryptoPP::byte*>(&iv[0]), iv.size());
}

std::string Cipher::getIVPlaintext()
{
    return std::string(reinterpret_cast<const char*>(&d_iv[0]), d_iv.size());
}
