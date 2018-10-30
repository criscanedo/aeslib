# AesEncryption
Personal encryption library to perform AES CBC encryption/decryption with prepended IV. Acts as a wrapper around [Crypto++](https://www.cryptopp.com/) library.

## Advanced Encryption Standard

### Description

[AES](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard), originally named Rijndael, was established as specification of encryption by U.S. NIST in 2001. It is a symmetric-key algorithm with a fixed block size of 128 bits and a key size of 128, 192, or 256 bits. Its cipher operates using [Rijndael's key schedule](https://en.wikipedia.org/wiki/Rijndael_key_schedule) to derive additional keys for each round of transformation. The rounds are determined based on the size of the original keys.

* 10 rounds: 128 bit-key
* 12 rounds: 192-bit key
* 14 rounds: 256-bit key

## Block Cipher Mode of Operation
[Cipher Block Chaining (CBC)](https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#Cipher_Block_Chaining_(CBC)) is the mode of operation that is being used in this library. While it is generally recommended to include a hash-based message authentication code (HMAC) with CBC, I've written this library to begin with a practical minimum and work my way up to include authenticated symmetric-key encryption soon.

CBC uses an [initialization vector (IV)](https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#Initialization_vector_(IV)) that is the size of AES's block size (128-bit). The IV is used to ensure unique ciphertext with every encryption. Without it, two plaintext messages would produce the same ciphertext output. It is highly recommend that a IV be generated randomly for each encryption, and to never use the same IV more than once under the same key.

The algorithm itself XORs each block of plaintext with the previous block of ciphertext before being encrypted. The IV is used with the plaintext for the first block of plaintext.

## Padding

Some libraries generally require specifying a [padding algorithm](https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#Padding) such as Java's [Cipher class](https://docs.oracle.com/javase/7/docs/api/javax/crypto/Cipher.html) or .NET's [Aes class](https://docs.microsoft.com/en-us/dotnet/api/system.security.cryptography.aes?view=netframework-4.7.2).

This is where Crypto++ differs in its implementation. While padding is still required, Crypto++ features a high level abstraction that handles buffering input, buffering output, and padding for you. The paradigm is called [pipelining](https://www.cryptopp.com/wiki/Pipelining) and was modeled from the Unix pipe system.

While it's not necessary to know the details of Crypto++ to effectively use this library, it's never a bad investment to add to your arsenal of tools. It may lead you to write a better implementation for yourself.

## AesCrypto Implementation

### Key and IV

Both the key and iv in AesCrypto are of type CryptoPP::SecByteBlock which is a class that provides secure storage that is zeroized or wiped upon destruction. The actual class itself is defined as **SecBlock<type>**. SecByteBlock is simply a typedef for **SecBlock<byte>**.

In AesCrypto, SecByteBlock is a typedef for [CryptoPP::SecByteBlock](https://www.cryptopp.com/wiki/SecBlock).

To create a SecByteBlock using AesCrypto:

    #include "aescrypto.h"

    int main(int argc, char** argv)
    {
        // create a 128-bit sized SecByteBlock
        SecByteBlock key(AesCrypto::DEFAULT_KEYLENGTH);

        return 0;
    }

The key sizes and block size are accessible through the following static members:

    AesCrypto::DEFAULT_KEYLENGTH; // 16 byte
    AesCrypto::MIN_KEYLENGTH;     // 16 byte
    AesCrypto::MAX_KEYLENGTH;     // 32 byte
    AesCrypto::BLOCKSIZE;         // 16 byte

You may also randomly generate a key and iv using AesCrypto:

    #include "aescrypto.h"

    int main(int argc, char** argv)
    {
        AesCrypto aes;

        // Randomly generates and sets both key and IV
        aes.generateKey();
        aes.generateIv();

        return 0;
    }

### CBC Encryption/Decryption

I created this library specifically to handle prepending the of the IV in plaintext to the output ciphertext during encryption; as well as handling the extraction of the IV from the ciphertext during decryption.

All of this takes place within the following member functions:

    std::string cbcEncrypt(std::string plaintext) const;
    std::string cbcDecrypt(std::string ciphertext) const;

You only ever need to provide the data that you wish to encrypt or decrypt to these functions so long as the key and iv have been set.

### Utility

Currently there are two member functions to help with conversion from string to SecByteBlock or vice versa:

    std::string blockToString(SecByteBlock byteBlock) const;
    SecByteBlock toByteBlock(std::string str) const;

### Usage

    #include <string>
    #include "aescrypto.h"

    int main(int argc, char** argv)
    {
        AesCrypto aes;

        // Randomly generate and set both key and IV
        aes.generateKey();
        aes.generateIV();

        std::string plaintext = "This is plaintext.";

        std::string ciphertext = aes.cbcEncrypt(plaintext);

        std::string roundtrip = aes.cbcDecrypt(ciphertext);

        return 0;
    }
