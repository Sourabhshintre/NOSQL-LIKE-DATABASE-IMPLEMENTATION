#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <unordered_map>
#include <vector>

// Represents a document in your NoSQL-like database
class Document {
public:
    // A map where each key-value pair represents a field in the document
    std::unordered_map<std::string, std::string> data;

    // Optionally, you can add other member functions or constructors here
    Document() = default;
    Document(const std::unordered_map<std::string, std::string>& initialData) : data(initialData) {}

    // Function to add or update a field in the document
    void setField(const std::string& key, const std::string& value) {
        data[key] = value;
    }

    // Function to get a field value from the document
    std::string getField(const std::string& key) const {
        auto it = data.find(key);
        if (it != data.end()) {
            return it->second;
        }
        return ""; // Return an empty string if the key does not exist
    }
};

#endif // DOCUMENT_H
