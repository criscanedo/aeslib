// cipher.h
#ifndef INCLUDED_CIPHER
#define INCLUDED_CIPHER

#include <string>
#include <crypto/secblock.h>
#include <crypto/cryptlib.h>
#include <crypto/filters.h>

class Cipher {
private:
    CryptoPP::SecByteBlock d_key;
    CryptoPP::SecByteBlock d_iv;
    CryptoPP::StringSink* d_stringSink_p;
    CryptoPP::StreamTransformationFilter* d_streamTransFilter_p;

    static CryptoPP::AutoSeededRandomPool s_rand;

public:
    // CREATORS
    Cipher();

    static std::string encrypt(std::string plaintext);
    static std::string decrypt(std::string ciphertext);

    // MANIPULATORS
    static CryptoPP::SecByteBlock generateKey();
    static CryptoPP::SecByteBlock generateIV();
    static void setKey(std::string key);
    static void setIV(std::string iv);
    static void setStringSink(std::string text);
    static void setStreamTransFilter(CryptoPP::BufferedTransformation& blockCipher, CryptoPP::StringSink* stringSink);

    // ACCESSORS
    std::string getIVPlaintext();
};

#endif
