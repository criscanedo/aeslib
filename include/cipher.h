// cipher.h
#ifndef INCLUDED_CIPHER
#define INCLUDED_CIPHER

#include <string>
#include <crypto/secblock.h>

class cipher {
private:
    typedef unsigned char byte;

    CryptoPP::SecByteBlock d_key;
    CryptoPP::SecByteBlock d_iv;

public:
    static std::string encrypt(std::string plaintext);
    static std::string decrypt(std::string ciphertext);

    // MANIPULATORS
    void setKey(std::string key);
    void setIV(std::string iv);
};

#endif
