#include <catch.hpp>
#include "aescrypto.h"

SCENARIO("creating AesCrypto type has key and iv initialized to default size and memset to 0", "[createAes]")
{
    // Arrange
    SecByteBlock mockIv(AesCrypto::BLOCKSIZE);
    SecByteBlock mockKey(AesCrypto::DEFAULT_KEYLENGTH);
    std::memset(mockIv, 0x00, mockIv.size());
    std::memset(mockKey, 0x00, mockKey.size());

    // Act
    AesCrypto crypto;
    auto actualIv = crypto.getIv();
    auto actualKey = crypto.getKey();

    // Assert
    REQUIRE(mockIv == actualIv);
    REQUIRE(mockKey == actualKey);
}
