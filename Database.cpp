#include "Database.h"
#include "Encryption.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

// Constructor
Database::Database() {}

// Register a new user
void Database::registerUser(const std::string& username, const std::string& password) {
    if (users.find(username) != users.end()) {
        throw std::runtime_error("User already exists.");
    }
    std::string encryptedPassword = polyalphabeticEncrypt(password, "YourEncryptionKey");
    users[username] = {encryptedPassword, {}};
}

// Login a user
bool Database::loginUser(const std::string& username, const std::string& password) {
    auto it = users.find(username);
    if (it != users.end()) {
        std::string encryptedPassword = polyalphabeticEncrypt(password, "YourEncryptionKey");
        return it->second.first == encryptedPassword;
    }
    return false;
}

// Add a new collection
void Database::addCollection(const std::string& username, const std::string& collectionName) {
    auto it = users.find(username);
    if (it != users.end()) {
        it->second.second[collectionName] = {};
    } else {
        throw std::runtime_error("User not found.");
    }
}

// Add a document to a collection
void Database::addDocument(const std::string& username, const std::string& collectionName, const Document& doc) {
    auto it = users.find(username);
    if (it != users.end()) {
        auto& collections = it->second.second;
        auto collIt = collections.find(collectionName);
        if (collIt != collections.end()) {
            collIt->second.push_back(doc);
        } else {
            throw std::runtime_error("Collection not found.");
        }
    } else {
        throw std::runtime_error("User not found.");
    }
}

// Get documents from a collection
std::vector<Document> Database::getDocuments(const std::string& username, const std::string& collectionName) {
    auto it = users.find(username);
    if (it != users.end()) {
        auto& collections = it->second.second;
        auto collIt = collections.find(collectionName);
        if (collIt != collections.end()) {
            return collIt->second;
        } else {
            throw std::runtime_error("Collection not found.");
        }
    } else {
        throw std::runtime_error("User not found.");
    }
}

// Update a document in a collection
void Database::updateDocument(const std::string& username, const std::string& collectionName, unsigned int docIndex, const Document& updatedDoc) {
    auto it = users.find(username);
    if (it != users.end()) {
        auto& collections = it->second.second;
        auto collIt = collections.find(collectionName);
        if (collIt != collections.end()) {
            if (docIndex < collIt->second.size()) {
                collIt->second[docIndex] = updatedDoc;
            } else {
                throw std::runtime_error("Document index out of range.");
            }
        } else {
            throw std::runtime_error("Collection not found.");
        }
    } else {
        throw std::runtime_error("User not found.");
    }
}

// Delete a document from a collection
void Database::deleteDocument(const std::string& username, const std::string& collectionName, unsigned int docIndex) {
    auto it = users.find(username);
    if (it != users.end()) {
        auto& collections = it->second.second;
        auto collIt = collections.find(collectionName);
        if (collIt != collections.end()) {
            if (docIndex < collIt->second.size()) {
                collIt->second.erase(collIt->second.begin() + docIndex);
            } else {
                throw std::runtime_error("Document index out of range.");
            }
        } else {
            throw std::runtime_error("Collection not found.");
        }
    } else {
        throw std::runtime_error("User not found.");
    }
}

// List all collections for a user
std::vector<std::string> Database::listCollections(const std::string& username) {
    auto it = users.find(username);
    if (it != users.end()) {
        std::vector<std::string> collectionNames;
        for (const auto& pair : it->second.second) {
            collectionNames.push_back(pair.first);
        }
        return collectionNames;
    } else {
        throw std::runtime_error("User not found.");
    }
}

// List all documents in a collection
std::vector<Document> Database::listDocuments(const std::string& username, const std::string& collectionName) {
    auto it = users.find(username);
    if (it != users.end()) {
        auto& collections = it->second.second;
        auto collIt = collections.find(collectionName);
        if (collIt != collections.end()) {
            return collIt->second;
        } else {
            throw std::runtime_error("Collection not found.");
        }
    } else {
        throw std::runtime_error("User not found.");
    }
}

// Save the database to a file
void Database::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file.");
    }

    for (const auto& userPair : users) {
        const std::string& username = userPair.first;
        const auto& user = userPair.second;

        file << username << '\n';
        file << user.first << '\n'; // Encrypted password

        for (const auto& collectionPair : user.second) {
            const std::string& collectionName = collectionPair.first;
            const auto& documents = collectionPair.second;

            file << collectionName << '\n';
            file << documents.size() << '\n';

            for (const auto& doc : documents) {
                file << doc.data.size() << '\n';
                for (const auto& field : doc.data) {
                    file << field.first << '\n' << field.second << '\n';
                }
            }
        }
    }
}

// Load the database from a file
void Database::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file.");
    }

    std::string username;
    while (std::getline(file, username)) {
        std::string encryptedPassword;
        std::getline(file, encryptedPassword);

        users[username] = {encryptedPassword, {}};

        std::string collectionName;
        while (std::getline(file, collectionName)) {
            size_t numDocs;
            file >> numDocs;
            file.ignore(); // Ignore the newline character after the number

            std::vector<Document> documents;
            for (size_t i = 0; i < numDocs; ++i) {
                size_t numFields;
                file >> numFields;
                file.ignore();

                Document doc;
                for (size_t j = 0; j < numFields; ++j) {
                    std::string key, value;
                    std::getline(file, key);
                    std::getline(file, value);
                    doc.setField(key, value);
                }
                documents.push_back(doc);
            }
            users[username].second[collectionName] = documents;
        }
    }
}
