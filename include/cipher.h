// cipher.h
#ifndef INCLUDED_CIPHER
#define INCLUDED_CIPHER

#include <string>
#include <crypto/osrng.h>
#include <crypto/secblock.h>
#include <crypto/cryptlib.h>
#include <crypto/filters.h>

struct Cipher {
private:
    static int _ivSize;
    CryptoPP::SecByteBlock d_key;
    CryptoPP::SecByteBlock d_iv;

    static CryptoPP::AutoSeededRandomPool s_rand;
    static bool s_isKeySet;

public:
    static std::string encrypt(std::string plaintext);
    static std::string decrypt(std::string ciphertext);

    // MANIPULATORS
    static bool setKey(std::string key);
    static void setIV(std::string iv);
    static CryptoPP::SecByteBlock generateKey();
    static CryptoPP::SecByteBlock generateIV();

    static std::string ivToPlaintext(CryptoPP::SecByteBlock iv);
    static std::string extractIV(std::string ciphertext);

    static std::string encode64(std::string text);
    static std::string decode64(std::string text);
};

#endif
