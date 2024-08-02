#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <unordered_map>
#include <vector>
#include "Document.h"

class Database {
public:
    Database();

    void registerUser(const std::string& username, const std::string& password);
    bool loginUser(const std::string& username, const std::string& password);

    void addCollection(const std::string& username, const std::string& collectionName);
    void addDocument(const std::string& username, const std::string& collectionName, const Document& doc);
    
    std::vector<Document> getDocuments(const std::string& username, const std::string& collectionName);
    void updateDocument(const std::string& username, const std::string& collectionName, unsigned int docIndex, const Document& updatedDoc);
    void deleteDocument(const std::string& username, const std::string& collectionName, unsigned int docIndex);

    std::vector<std::string> listCollections(const std::string& username);
    std::vector<Document> listDocuments(const std::string& username, const std::string& collectionName);

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);

private:
    // Internal data structure for users and their data
    std::unordered_map<std::string, std::pair<std::string, std::unordered_map<std::string, std::vector<Document>>>> users;
};

#endif // DATABASE_H
