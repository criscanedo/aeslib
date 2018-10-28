#include <catch.hpp>
#include <crypto/secblock.h>
#include "aescrypto.h"

class AESCryptoFixture {
protected:
    AESCrypto aescrypto;
    int defaultKeySize = 16;
    int defaultBlockSize = 16;

public:
    AESCryptoFixture()
    {
    }
};

TEST_CASE_METHOD(AESCryptoFixture, "create AESCrypto with default key and block size", "[createAES]")
{
    REQUIRE(aescrypto.getKeySize() == defaultKeySize);
    REQUIRE(aescrypto.getBlockSize() == defaultBlockSize);
}

TEST_CASE_METHOD(AESCryptoFixture, "create AESCrypto with key and iv initalized to default size","[createAES]")
{
    CryptoPP::SecByteBlock expectedKey(defaultKeySize);
    CryptoPP::SecByteBlock expectedIv(defaultBlockSize);
    std::memset(expectedKey, 0x00, expectedKey.size());
    std::memset(expectedIv, 0x00, expectedIv.size());

    CryptoPP::SecByteBlock actualKey = aescrypto.getKey();
    CryptoPP::SecByteBlock actualIv = aescrypto.getIv();

    REQUIRE(expectedKey == actualKey);
    REQUIRE(expectedIv == actualIv);
}

TEST_CASE_METHOD(AESCryptoFixture, "set key and iv", "[key][iv]")
{
    // valid key sizes in bytes: 16, 24, 32
    // valid iv sizes in bytes: 16

    GIVEN("key or iv of invalid size, exception is thrown")
    {
        int notValid = 1000;
        int alsoNotValid = 1;
        CryptoPP::SecByteBlock invalidAesKey(notValid);
        CryptoPP::SecByteBlock invalidAesIv(alsoNotValid);

        REQUIRE_THROW(aescrypto.setKey(invalidAesKey));
        REQUIRE_THROW(aescrypto.setIv(invalidAesIv));
    }

    GIVEN("key or iv of valid size, no exception is thrown")
    {
        int maxValidSize = defaultKeySize << 1;
        CryptoPP::SecByteBlock validAesKey(defaultKeySize);
        CryptoPP::SecByteBlock validAesIv(defaultBlockSize);

        for(int i = defaultKeySize; i < maxValidSize; i+=8) {
        }
    }
}
