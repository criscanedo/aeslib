#include <catch.hpp>
#include "aescrypto.h"

SCENARIO("setting key", "[set][key]")
{
    AesCrypto crypto;
    SecByteBlock mockIv(AesCrypto::DEFAULT_KEYLENGTH);

    GIVEN("key of invalid size, exception is thrown")
    {
        int invalidSize = 10;

        mockIv.CleanNew(invalidSize);

        REQUIRE_THROWS(crypto.setKey(mockIv));
    }

    GIVEN("key of valid size, no exception is thrown")
    {
        REQUIRE_NOTHROW(crypto.setKey(mockIv));

        mockIv.CleanNew(mockIv.size() + 8);
        REQUIRE_NOTHROW(crypto.setKey(mockIv));

        mockIv.CleanNew(mockIv.size() + 8);
        REQUIRE_NOTHROW(crypto.setKey(mockIv));

        AND_WHEN("no exception is thrown, key is properly set")
        {
            crypto.setKey(mockIv);
            SecByteBlock actualKey = crypto.getKey();

            CHECK(mockIv == actualKey);
        }

        WHEN("key of greater size is set")
        {
            mockIv.CleanNew(mockIv.size() + 8);
            crypto.setKey(mockIv);
            actualKey = crypto.getKey();
            
            REQUIRE(mockIv == actualKey);

            mockIv.CleanNew(mockIv.size() + 8);
            crypto.setKey(mockIv);
            actualKey = crypto.getKey();

            REQUIRE(mockIv == actualKey);
        }

        WHEN("key of lesser size is set")
        {
            mockIv.CleanNew(AesCrypto::MAX_KEYLENGTH);
            crypto.setKey(mockIv);
            actualKey = crypto.getKey();
            
            CHECK(actualKey.size() == AesCrypto::MAX_KEYLENGTH);

            mockIv.CleanNew(mockIv.size() - 8);
            crypto.setKey(mockIv);
            actualKey = crypto.getKey();

            REQUIRE(mockIv == actualKey);

            mockIv.CleanNew(mockIv.size() - 8);
            crypto.setKey(mockIv);
            actualKey = crypto.getKey();

            REQUIRE(mockIv == actualKey);
        }
    }
}

SCENARIO("setting iv", "[set][iv]")
{
    AesCrypto crypto;
    SecByteBlock mockIv(AesCrypto::BLOCKSIZE);
    
    GIVEN("iv of invalid size, exception is thrown")
    {
        int invalidSize = 10;

        mockIv.CleanNew(invalidSize);

        REQUIRE_THROWS(crypto.setIv(mockIv));
    }

    GIVEN("iv of valid size, no exception is thrown")
    {
        REQUIRE_NOTHROW(crypto.setIv(mockIv));
    }
}
