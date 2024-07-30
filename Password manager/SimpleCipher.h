//
// Created by Gor on 01/06/2023.
//
#include <iomanip>
#include <sstream>
#ifndef S27734_SIMPLECIPHER_H
#define S27734_SIMPLECIPHER_H

class SimpleCipher {
private:
    std::map<char, int> encryptionMap;

public:
    SimpleCipher();
    std::string encrypt(const std::string& plaintext);
    std::string decrypt(const std::string& ciphertext);
};



#endif //S27734_SIMPLECIPHER_H
