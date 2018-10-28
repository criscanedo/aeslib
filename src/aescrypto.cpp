#include <iostream>
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
using CryptoPP::BufferedTransformation;
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::SecByteBlock;

CryptoPP::AutoSeededRandomPool AESCrypto::s_rand;

AESCrypto::AESCrypto()
{
    d_key = SecByteBlock(AES::DEFAULT_KEYLENGTH);
    d_iv = SecByteBlock(AES::BLOCKSIZE);
    std::memset(d_key, 0x00, d_key.size());
    std::memset(d_iv, 0x00, d_iv.size());
}

std::string AESCrypto::cbcEncrypt(std::string plaintext) const
{
    std::string iv = ivToString(d_iv);
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

std::string AESCrypto::ivToString(CryptoPP::SecByteBlock iv) const
{
    if (iv.size() < AES::BLOCKSIZE) {
        throw std::runtime_error("iv: Not a valid size.");
    }

    return std::string(reinterpret_cast<const char*>(&iv[0]), iv.size());
}

std::string AESCrypto::cbcDecrypt(std::string ciphertext) const
{
    std::string ivString = extractIv(ciphertext);
    SecByteBlock iv = toByteBlock(ivString);
    ciphertext = ciphertext.substr(AES::BLOCKSIZE);
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

std::string AESCrypto::extractIv(std::string ciphertext) const
{
    return ciphertext.substr(0, AES::BLOCKSIZE);
}

SecByteBlock AESCrypto::toByteBlock(std::string str) const
{
    return SecByteBlock(reinterpret_cast<const byte*>(&str[0]), str.size());
}

void AESCrypto::setKey(CryptoPP::SecByteBlock key)
{
    if (!isValidKeySize(key.size()))
        throw std::runtime_error("key: Not a valid size.");

    d_key.New(key.size());
    d_key = key;
}

void AESCrypto::setIv(CryptoPP::SecByteBlock iv)
{
    if (iv.size() != AES::BLOCKSIZE)
        throw std::runtime_error("iv: Not a valid size.");

    d_iv.New(AES::BLOCKSIZE);
    d_iv = iv;
}

void AESCrypto::generateKey()
{
    d_key.New(AES::DEFAULT_KEYLENGTH);
    s_rand.GenerateBlock(d_key, d_key.size());
}

void AESCrypto::generateIv()
{
    d_iv.New(AES::BLOCKSIZE);
    s_rand.GenerateBlock(d_iv, d_iv.size());
}

SecByteBlock AESCrypto::getKey() const
{
    return d_key;
}

SecByteBlock AESCrypto::getIv() const
{
    return d_iv;
}

int AESCrypto::getBlockSize() const
{
    return AES::BLOCKSIZE;
}

int AESCrypto::getKeySize() const
{
    return d_key.size();
}

bool AESCrypto::isValidKeySize(int size)
{
    int aesSize = AES::MIN_KEYLENGTH;

    return ((aesSize == size) ||
           ((aesSize + 8) == size) ||
           ((aesSize << 1) == size));
}
