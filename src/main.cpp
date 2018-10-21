#include <iostream>
#include <string>
using std::string;

int main()
{
    string plaintext, ciphertext, encoded, decoded;
    string key;

    std::cout << "Enter the plaintext to encrypt: ";
    std::cin >> plaintext;

    std::cout << "Enter key to encrypt/decrypt with: ";
    std::cin >> key;

    Cipher::setKey(key);
    Cipher::generateIV();

    ciphertext = Cipher::encrypt(plaintext);
    std::cout << "\nCiphertext: " << ciphertext << std::endl;

    encoded = Cipher::encode64(ciphertext);
    std::cout << "\nEncoded: " << encoded << std::endl;

    decoded = Cipher::decode64(encoded);
    std::cout << "\nDecoded: " << decoded << std::endl;

    ciphertext = cipher::decrypt(ciphertext);
    std::cout << "\nDecrypted: " << ciphertext << std::endl;

    return 0;
}
/*
string encrypt(string plaintext, string ekey, byte* eiv)
{
    string Ciphertext, ivplaintext;
    SecByteBlock key(reinterpret_cast<const byte*>(&ekey[0]), ekey.size());
    SecByteBlock iv(eiv, eiv.size());
    ivplaintext = std::string(reinterpret_cast<const char*>(&iv[0]), iv.size());
    
    // Prepend unencrypted IV to Cipher before encryption
    Ciphertext = ivplaintext;

    try {
        CBC_MODE<AES>::Encryption blockCipher;
        blockCipher.setKeyWithIv(key, key.size(), iv);

        CryptoPP::StringSource ss(plaintext, true, new StreamTransformationFilter(blockCipher, new StringSink(ciphertext)));
        return Ciphertext;
    }
    catch(const CryptoPP::Exception& e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

string decrypt(string Ciphertext, string ekey)
{
    string plaintext, ivplaintext;

    // Copy first 16 bytes from Ciphertext
    ivplaintext = Ciphertext.substr(0, AES::BLOCKSIZE);

    // Remove IV from Ciphertext
    Ciphertext = ciphertext.substr(AES::BLOCKSIZE);

    try {
        SecByteBlock key(reinterpret_cast<const byte*>(&ekey[0]), ekey.size());
        SecByteBlock iv(reinterpret_cast<const byte*>(&ivplaintext[0]), ivplaintext.size());
        CBC_MODE<AES>::Decryption blockCipher;
        blockCipher.setKeyWithIv(key, key.size(), iv);

        CryptoPP::StringSource ss(Ciphertext, true, new StreamTransformationFilter(blockCipher, new StringSink(plaintext)));
        return plaintext;
    }
    catch(const CryptoPP::Exception& e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
} */
