//
// Created by Gor on 01/06/2023.
//
//
// Created by Gor on 30/05/2023.
//

#include <map>
#include "SimpleCipher.h"

SimpleCipher::SimpleCipher() {
    for (char c = 'a'; c <= 'z'; ++c) {
        encryptionMap[c] = 'z' - (c - 'a');
    }
    for (char c = 'A'; c <= 'Z'; ++c) {
        encryptionMap[c] = 'Z' - (c - 'A');
    }
}
/// @brief Metoda szyfrująca hasła
std::string SimpleCipher::encrypt(const std::string& plaintext) {
    std::string ciphertext;
    for (char c : plaintext) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            ciphertext += encryptionMap[c];
        } else {
            ciphertext += c;
        }
    }
    return ciphertext;
}
/// @brief Metoda deszyfrująca hasła
std::string SimpleCipher::decrypt(const std::string& ciphertext) {
    return encrypt(ciphertext);
}


