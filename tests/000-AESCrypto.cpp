#include <catch.hpp>
#include <crypto/secblock.h>
#include "aescrypto.h"

class AESCryptoFixture {
protected:
    AESCrypto aescrypto;
    int defKeySize = 16;
    int defBlockSize = 16;

public:
    AESCryptoFixture()
    {
    }
};

TEST_CASE_METHOD(AESCryptoFixture, "Create AESCrypto with default size", "[createAES]")
{
    REQUIRE(aescrypto.getKeySize() == defKeySize);
    REQUIRE(aescrypto.getBlockSize() == defBlockSize);
}

TEST_CASE_METHOD(AESCryptoFixture, "Create AESCrypto with key and iv initalized to default size","[createAES]")
{
    CryptoPP::SecByteBlock expectedKey(defKeySize);
    CryptoPP::SecByteBlock expectedIv(defBlockSize);

    std::memset(expectedKey, 0x00, expectedKey.size());
    std::memset(expectedIv, 0x00, expectedIv.size());

    CryptoPP::SecByteBlock actualKey = aescrypto.getKey();
    CryptoPP::SecByteBlock actualIv = aescrypto.getIv();

    REQUIRE(expectedKey == actualKey);
    REQUIRE(expectedIv == actualIv);
}
