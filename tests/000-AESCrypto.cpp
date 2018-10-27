#include <catch.hpp>
#include "aescrypto.h"

class AESCryptoFixture {
protected:
    AESCrypto aescrypto;
    int keySize = 16;
    int blockSize = 16;

public:
    AESCryptoFixture()
    {
    }
};

TEST_CASE_METHOD(AESCryptoFixture, "Instatiate AESCrypto instance", "[createAES]")
{
    REQUIRE(aescrypto.getKeySize() == keySize);
    REQUIRE(aescrypto.getBlockSize() == blockSize);
}
