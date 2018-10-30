// aescrypto.h
#ifndef INCLUDED_AESCRYPTO
#define INCLUDED_AESCRYPTO

#include <string>
#include <crypto/secblock.h>
#include <crypto/osrng.h>

typedef CryptoPP::SecByteBlock SecByteBlock;

class AesCrypto {
private:
    SecByteBlock d_iv;
    SecByteBlock d_key;

    static CryptoPP::AutoSeededRandomPool s_rand;

    std::string extractIv(std::string ciphertext) const;
    bool isValidKeySize(int size);

public:
    // CREATORS
    AesCrypto();

    // MANIPULATORS
    void generateIv();
    void generateKey();
    void setIv(SecByteBlock iv);
    void setKey(SecByteBlock key);

    // ACCESSORS
    SecByteBlock getIv() const;
    SecByteBlock getKey() const;

    std::string cbcEncrypt(std::string plaintext) const;
    std::string cbcDecrypt(std::string ciphertext) const;

    std::string blockToString(SecByteBlock byteBlock) const;
    SecByteBlock toByteBlock(std::string str) const;

    static const int DEFAULT_KEYLENGTH;
    static const int MIN_KEYLENGTH;
    static const int MAX_KEYLENGTH;
    static const int BLOCKSIZE;
};

#endif
