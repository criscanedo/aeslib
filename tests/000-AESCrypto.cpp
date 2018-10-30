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

SCENARIO("setting keys and iv", "[key][iv]")
{
    // Arrange
    AesCrypto crypto;
    SecByteBlock mockIv(AesCrypto::BLOCKSIZE);
    SecByteBlock mockKey(AesCrypto::DEFAULT_KEYLENGTH);

    GIVEN("key or iv of invalid size, exception is thrown")
    {
        int invalidSize = 10;

        // Act: Resize key and iv to an invalid size of 10 bytes
        mockIv.CleanNew(invalidSize);
        mockKey.CleanNew(invalidSize);

        // Assert
        REQUIRE_THROWS(crypto.setKey(mockKey));
        REQUIRE_THROWS(crypto.setIv(mockIv));
    }

    GIVEN("key or iv of valid size, no exception is thrown")
    {
        // Assert: Set default 16 byte key and 16 byte iv
        REQUIRE_NOTHROW(crypto.setIv(mockIv));
        REQUIRE_NOTHROW(crypto.setKey(mockKey));

        // Act and Assert: Resize key to 24 bytes
        mockKey.CleanNew(mockKey.size() + 8);
        REQUIRE_NOTHROW(crypto.setKey(mockKey));

        // Act and Assert: Resize key to 32 bytes
        mockKey.CleanNew(mockKey.size() + 8);
        REQUIRE_NOTHROW(crypto.setKey(mockKey));
    }

    GIVEN("valid key or iv, it is properly set")
    {
        // Act
        crypto.setIv(mockIv);
        crypto.setKey(mockKey);
        auto actualIv = crypto.getIv();
        auto actualKey = crypto.getKey();

        // Assert
        REQUIRE(mockIv == actualIv);
        REQUIRE(mockKey == actualKey);

        WHEN("key of greater size is set")
        {
            // Act: Increase size of key by 8 bytes and set
            mockKey.CleanNew(mockKey.size() + 8);
            crypto.setKey(mockKey);
            actualKey = crypto.getKey();

            // Assert
            REQUIRE(mockKey == actualKey);

            // Act: Increase size of key to max by another 8 bytes and set
            mockKey.CleanNew(mockKey.size() + 8);
            crypto.setKey(mockKey);
            actualKey = crypto.getKey();

            // Assert
            REQUIRE(mockKey == actualKey);
        }

        WHEN("key of lesser size is set")
        {
            // Arrange: Resize key to 32 bytes and set
            mockKey.CleanNew(AesCrypto::MAX_KEYLENGTH);
            crypto.setKey(mockKey);
            actualKey = crypto.getKey();
            
            // Check
            CHECK(actualKey.size() == AesCrypto::MAX_KEYLENGTH);

            // Act: Resize key to 24 bytes and set
            mockKey.CleanNew(mockKey.size() - 8);
            crypto.setKey(mockKey);
            actualKey = crypto.getKey();

            // Assert
            REQUIRE(mockKey == actualKey);

            // Act: Resize key to 16 bytes and set
            mockKey.CleanNew(mockKey.size() - 8);
            crypto.setKey(mockKey);
            actualKey = crypto.getKey();

            // Assert
            REQUIRE(mockKey == actualKey);
        }
    }
}
