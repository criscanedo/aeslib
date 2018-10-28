// aescrypto.h
#ifndef INCLUDED_AESCRYPTO
#define INCLUDED_AESCRYPTO

#include <string>
#include <crypto/osrng.h>
#include <crypto/secblock.h>
#include <crypto/cryptlib.h>
#include <crypto/filters.h>

class AESCrypto {
private:
    CryptoPP::SecByteBlock d_key;
    CryptoPP::SecByteBlock d_iv;
    static CryptoPP::AutoSeededRandomPool s_rand;

    std::string extractIv(std::string ciphertext) const;
    bool isValidKeySize(int size);

public:
    // CREATORS
    AESCrypto();

    // MANIPULATORS
    void setKey(CryptoPP::SecByteBlock key);
    void setIv(CryptoPP::SecByteBlock iv);
    void setKeySize(int sizeInBytes);
    void generateKey();
    void generateIv();

    // ACCESSORS
    CryptoPP::SecByteBlock getKey() const;
    CryptoPP::SecByteBlock getIv() const;
    int getBlockSize() const;
    int getKeySize() const;

    std::string cbcEncrypt(std::string plaintext) const;
    std::string cbcDecrypt(std::string ciphertext) const;
    std::string ivToString(CryptoPP::SecByteBlock iv) const;
    std::string keyToString(CryptoPP::SecByteBlock key) const;
    CryptoPP::SecByteBlock toByteBlock(std::string str) const;
};

#endif
