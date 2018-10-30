#include <string>
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
    }

    WHEN("key of greater size is set")
    {
        mockIv.CleanNew(mockIv.size() + 8);
        crypto.setKey(mockIv);
        SecByteBlock actualKey = crypto.getKey();
        
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
        SecByteBlock actualKey = crypto.getKey();
        
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

SCENARIO("generating a random key or iv sets them to the instance of AesCrypto", "[set][generate]")
{
    AesCrypto aes;

    SecByteBlock myKey = aes.toByteBlock("My distinguishable key!!");
    SecByteBlock myIv = aes.toByteBlock("My unique iv!!!!");
    aes.setKey(myKey);
    aes.setIv(myIv);

    GIVEN("a key and iv already set")
    {
        // Make sure our unique key and iv are set
        CHECK(aes.getKey() == myKey);
        CHECK(aes.getIv() == myIv);

        aes.generateKey();
        aes.generateIv();

        SecByteBlock currentKey = aes.getKey();
        SecByteBlock currentIv = aes.getIv();

        REQUIRE_FALSE(myKey == currentKey);
        REQUIRE_FALSE(myIv == currentIv);

    }

    AND_WHEN("generating a key or iv or more than once, a different value is produced and set")
    {
        aes.generateKey();
        aes.generateIv();
        SecByteBlock previousKey = aes.getKey();
        SecByteBlock previousIv = aes.getIv();

        aes.generateKey();
        aes.generateIv();
        SecByteBlock currentKey = aes.getKey();
        SecByteBlock currentIv = aes.getIv();

        REQUIRE_FALSE(previousKey == currentKey);
        REQUIRE_FALSE(previousIv == currentIv);
    }
}
