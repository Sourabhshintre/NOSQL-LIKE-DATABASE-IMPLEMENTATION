#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include "Database.h" // Ensure this includes Document definition

std::string modifiedCaesarCipher(const std::string& text, int shift);
std::string polyalphabeticEncrypt(const std::string& text, const std::string& key);
void encryptDocument(Document& doc, int shift);
void decryptDocument(Document& doc, int shift);

#endif // ENCRYPTION_H
