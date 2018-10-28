#include <catch.hpp>
#include <crypto/secblock.h>
#include <crypto/aes.h>
#include "aescrypto.h"

SCENARIO("creating AESCrypto type has default key and block size", "[createAes]")
{
    AESCrypto crypto;

    REQUIRE(crypto.getKeySize() == CryptoPP::AES::DEFAULT_KEYLENGTH);
    REQUIRE(crypto.getBlockSize() == CryptoPP::AES::BLOCKSIZE);
}

SCENARIO("creating AESCrypto type has key and iv initialized to default size and 0", "[createAes]")
{
    // Arrange
    CryptoPP::SecByteBlock mockIv(CryptoPP::AES::BLOCKSIZE);
    CryptoPP::SecByteBlock mockKey(CryptoPP::AES::DEFAULT_KEYLENGTH);
    std::memset(mockIv, 0x00, mockIv.size());
    std::memset(mockKey, 0x00, mockKey.size());

    // Act
    AESCrypto crypto;
    auto actualIv = crypto.getIv();
    auto actualKey = crypto.getKey();

    // Assert
    REQUIRE(mockIv == actualIv);
    REQUIRE(mockKey == actualKey);
}

SCENARIO("setting keys and iv", "[key][iv]")
{
    AESCrypto crypto;
    CryptoPP::SecByteBlock mockIv(CryptoPP::AES::BLOCKSIZE);
    CryptoPP::SecByteBlock mockKey(CryptoPP::AES::DEFAULT_KEYLENGTH);

    GIVEN("key or iv of invalid size, exception is thrown")
    {
        int invalidSize = 10;

        // Resize key and iv to an invalid size of 10 bytes
        mockIv.CleanNew(invalidSize);
        mockKey.CleanNew(invalidSize);

        REQUIRE_THROWS(crypto.setKey(mockKey));
        REQUIRE_THROWS(crypto.setIv(mockIv));
    }

    GIVEN("key or iv of valid size, no exception is thrown")
    {
        // Resize key to 16 bytes
        REQUIRE_NOTHROW(crypto.setIv(mockIv));
        REQUIRE_NOTHROW(crypto.setKey(mockKey));

        // Resize key to 24 bytes
        mockKey.CleanNew(mockKey.size() + 8);
        REQUIRE_NOTHROW(crypto.setKey(mockKey));

        // Resize key to 32 bytes
        mockKey.CleanNew(mockKey.size() + 8);
        REQUIRE_NOTHROW(crypto.setKey(mockKey));
    }

    GIVEN("valid key or iv, it is properly set")
    {
        // Get and set default key and iv
        crypto.setIv(mockIv);
        crypto.setKey(mockKey);
        auto actualIv = crypto.getIv();
        auto actualKey = crypto.getKey();

        REQUIRE(mockIv == actualIv);
        REQUIRE(mockKey == actualKey);

        WHEN("key of greater size is set")
        {
            // Increase size of key by 8 bytes and set
            mockKey.CleanNew(mockKey.size() + 8);
            crypto.setKey(mockKey);
            actualKey = crypto.getKey();

            REQUIRE(mockKey == actualKey);

            // Increase size of key to max by another 8 bytes and set
            mockKey.CleanNew(mockKey.size() + 8);
            crypto.setKey(mockKey);
            actualKey = crypto.getKey();

            REQUIRE(mockKey == actualKey);
        }

        WHEN("key of lesser size is set")
        {
            // Resize key to 32 bytes and set
            mockKey.CleanNew(CryptoPP::AES::MAX_KEYLENGTH);
            crypto.setKey(mockKey);
            actualKey = crypto.getKey();

            // Resize key to 24 bytes and set
            mockKey.CleanNew(mockKey.size() - 8);
            crypto.setKey(mockKey);
            actualKey = crypto.getKey();

            REQUIRE(mockKey == actualKey);

            // Resize key to 16 bytes and set
            mockKey.CleanNew(mockKey.size() - 8);
            crypto.setKey(mockKey);
            actualKey = crypto.getKey();

            REQUIRE(mockKey == actualKey);
        }
    }
}
