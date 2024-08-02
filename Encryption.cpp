#include "Encryption.h"
#include "Document.h"

// Encrypts the text using a modified Caesar Cipher
std::string modifiedCaesarCipher(const std::string& text, int shift) {
    std::string result = text;
    for (char& c : result) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base + shift) % 26 + base;
        }
    }
    return result;
}

// Encrypts the text using a polyalphabetic cipher
std::string polyalphabeticEncrypt(const std::string& text, const std::string& key) {
    std::string result = text;
    int keyLen = key.length();
    for (size_t i = 0; i < text.length(); ++i) {
        if (isalpha(text[i])) {
            char base = islower(text[i]) ? 'a' : 'A';
            result[i] = (text[i] - base + (key[i % keyLen] - base)) % 26 + base;
        }
    }
    return result;
}

// Encrypts the document by applying the Caesar Cipher to its data
void encryptDocument(Document& doc, int shift) {
    for (auto& pair : doc.data) {
        pair.second = modifiedCaesarCipher(pair.second, shift);
    }
}

// Decrypts the document by reversing the Caesar Cipher
void decryptDocument(Document& doc, int shift) {
    for (auto& pair : doc.data) {
        pair.second = modifiedCaesarCipher(pair.second, 26 - shift);
    }
}
