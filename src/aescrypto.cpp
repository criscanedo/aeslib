#include <string>
#include <crypto/cryptlib.h>
#include <crypto/osrng.h>
#include <crypto/aes.h>
#include <crypto/filters.h>
#include <crypto/modes.h>
#include <crypto/secblock.h>
#include "aescrypto.h"

using CryptoPP::byte;
using CryptoPP::AES;
using CryptoPP::CBC_Mode;
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

CryptoPP::AutoSeededRandomPool AesCrypto::s_rand;
const int AesCrypto::DEFAULT_KEYLENGTH = CryptoPP::AES::DEFAULT_KEYLENGTH;
const int AesCrypto::MIN_KEYLENGTH = CryptoPP::AES::MIN_KEYLENGTH;
const int AesCrypto::MAX_KEYLENGTH = CryptoPP::AES::MAX_KEYLENGTH;
const int AesCrypto::BLOCKSIZE = CryptoPP::AES::BLOCKSIZE;

AesCrypto::AesCrypto()
{
    d_key = SecByteBlock(DEFAULT_KEYLENGTH);
    d_iv = SecByteBlock(BLOCKSIZE);
    std::memset(d_key, 0x00, d_key.size());
    std::memset(d_iv, 0x00, d_iv.size());
}

std::string AesCrypto::cbcEncrypt(std::string plaintext) const
{
    std::string iv = blockToString(d_iv);
    std::string ciphertext;

    try {
        CBC_Mode<AES>::Encryption blockCipher;
        blockCipher.SetKeyWithIV(d_key, d_key.size(), d_iv, d_iv.size());

        StringSource ss(plaintext, true,
                        new StreamTransformationFilter(blockCipher,
                        new StringSink(ciphertext)));

        return (iv + ciphertext);
    }
    catch(const CryptoPP::Exception& e) {
        throw e;
    }
}

std::string AesCrypto::cbcDecrypt(std::string ciphertext) const
{
    std::string ivString = extractIv(ciphertext);
    SecByteBlock iv = toByteBlock(ivString);
    ciphertext = ciphertext.substr(BLOCKSIZE);
    std::string plaintext;

    try {
        CBC_Mode<AES>::Decryption blockCipher;
        blockCipher.SetKeyWithIV(d_key, d_key.size(), iv, iv.size());

        StringSource ss(ciphertext, true,
                        new StreamTransformationFilter(blockCipher,
                        new StringSink(plaintext)));

        return plaintext;
    }
    catch(const CryptoPP::Exception& e) {
        throw e;
    }
}

std::string AesCrypto::extractIv(std::string ciphertext) const
{
    return ciphertext.substr(0, BLOCKSIZE);
}

std::string AesCrypto::blockToString(SecByteBlock byteBlock) const
{
    return std::string(reinterpret_cast<const char*>(&byteBlock[0], byteBlock.size()));
}

SecByteBlock AesCrypto::toByteBlock(std::string str) const
{
    return SecByteBlock(reinterpret_cast<const byte*>(&str[0]), str.size());
}

void AesCrypto::setKey(CryptoPP::SecByteBlock key)
{
    if (!isValidKeySize(key.size()))
        throw std::runtime_error("key: Not a valid size.");

    d_key.CleanNew(key.size());
    d_key = key;
}

void AesCrypto::setIv(CryptoPP::SecByteBlock iv)
{
    if (iv.size() != BLOCKSIZE)
        throw std::runtime_error("iv: Not a valid size.");

    d_iv.CleanNew(BLOCKSIZE);
    d_iv = iv;
}

void AesCrypto::generateKey()
{
    d_key.New(DEFAULT_KEYLENGTH);
    s_rand.GenerateBlock(d_key, d_key.size());
}

void AesCrypto::generateIv()
{
    d_iv.New(BLOCKSIZE);
    s_rand.GenerateBlock(d_iv, d_iv.size());
}

SecByteBlock AesCrypto::getKey() const
{
    return d_key;
}

SecByteBlock AesCrypto::getIv() const
{
    return d_iv;
}

bool AesCrypto::isValidKeySize(int size)
{
    int aesSize = MIN_KEYLENGTH;

    return ((aesSize == size) ||
           ((aesSize + 8) == size) ||
           ((aesSize << 1) == size));
}
