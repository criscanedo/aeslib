// cipher.h
#ifndef INCLUDED_CIPHER
#define INCLUDED_CIPHER

#include <memory>
#include <string>
#include <crypto/secblock.h>
#include <crypto/cryptlib.h>
#include <crypto/filters.h>

struct Cipher {
private:
    CryptoPP::SecByteBlock d_key;
    CryptoPP::SecByteBlock d_iv;

    static CryptoPP::AutoSeededRandomPool s_rand;

public:
    static std::string encrypt(std::string plaintext);
    static std::string decrypt(std::string ciphertext);

    // MANIPULATORS
    static void setKey(std::string key);
    static void setIV(std::string iv);
    static CryptoPP::SecByteBlock generateKey();
    static CryptoPP::SecByteBlock generateIV();

    static std::string ivToPlaintext(CryptoPP::SecByteBlock iv);
    static std::string extractIV(std::string ciphertext);
};

#endif
