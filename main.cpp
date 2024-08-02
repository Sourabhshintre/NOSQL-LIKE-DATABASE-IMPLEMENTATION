#include <iostream>
#include <limits> // Include this header for std::numeric_limits
#include <vector>
#include <map>
#include <stdexcept>
#include <string>
#include "Database.h"
#include "Encryption.h"

// Function to display the menu
void showMenu() {
    std::cout << "---------------------------" << std::endl;
    std::cout << "1. Create Collection" << std::endl;
    // std::cout << "---------------------------" << std::endl;
    std::cout << "2. Add Document to Collection" << std::endl;
    //  std::cout << "---------------------------" << std::endl;
    std::cout << "3. Retrieve Documents from Collection" << std::endl;
    //  std::cout << "---------------------------" << std::endl;
    std::cout << "4. Update Document in Collection" << std::endl;
    //  std::cout << "---------------------------" << std::endl;
    std::cout << "5. Delete Document from Collection" << std::endl;
    //  std::cout << "---------------------------" << std::endl;
    std::cout << "6. List Collections" << std::endl;
    //  std::cout << "---------------------------" << std::endl;
    std::cout << "7. List Documents in Collection" << std::endl;
    //  std::cout << "---------------------------" << std::endl;
    std::cout << "8. Encrypt Document" << std::endl;
    //  std::cout << "---------------------------" << std::endl;
    std::cout << "9. Decrypt Document" << std::endl;
    //  std::cout << "---------------------------" << std::endl;
    std::cout << "10. Exit" << std::endl;
     std::cout << "---------------------------" << std::endl;
}

// Function to handle invalid input
void handleInvalidInput() {
    std::cin.clear(); // Clear error flag
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
}

// Function to check if a collection exists
bool collectionExists(Database& db, const std::string& collectionName) {
    std::vector<std::string> collections = db.listCollections("user1");
    for (const auto& name : collections) {
        if (name == collectionName) {
            return true;
        }
    }
    return false;
}

int main() {
    Database db;
    try {
        db.registerUser("user1", "password123");
        if (db.loginUser("user1", "password123")) {
             std::cout << "---------------------------" << std::endl;
            std::cout << "Login successful!" << std::endl;

            int choice;
            std::string collectionName, key, value;
            size_t docIndex;
            Document doc;
            int shift;

            while (true) {
                showMenu();
                std::cin >> choice;

                if (std::cin.fail()) {
                    handleInvalidInput();
                    std::cout << "Invalid input. Please enter a number." << std::endl;
                    continue;
                }

                switch (choice) {
                    case 1:
                        std::cout << "Enter collection name: ";
                        std::cin >> collectionName;
                        db.addCollection("user1", collectionName);
                        break;
                    case 2:
                        std::cout << "Enter collection name: ";
                        std::cin >> collectionName;
                        if (!collectionExists(db, collectionName)) {
                            std::cout << "Collection not found." << std::endl;
                            break;
                        }
                        doc.data.clear();
                        std::cout << "Enter key-value pairs (key value). Enter 'done' to finish: ";
                        while (std::cin >> key && key != "done") {
                            std::cin >> value;
                            doc.data[key] = value;
                        }
                        db.addDocument("user1", collectionName, doc);
                        break;
                    case 3:
                        std::cout << "Enter collection name: ";
                        std::cin >> collectionName;
                        if (!collectionExists(db, collectionName)) {
                            std::cout << "Collection not found." << std::endl;
                            break;
                        }
                        for (const auto& d : db.getDocuments("user1", collectionName)) {
                            for (const auto& pair : d.data) {
                                std::cout << pair.first << ": " << pair.second << std::endl;
                            }
                        }
                        break;
                    case 4:
                        std::cout << "Enter collection name: ";
                        std::cin >> collectionName;
                        if (!collectionExists(db, collectionName)) {
                            std::cout << "Collection not found." << std::endl;
                            break;
                        }
                        std::cout << "Enter document index: ";
                        std::cin >> docIndex;
                        if (docIndex >= db.getDocuments("user1", collectionName).size()) {
                            std::cout << "Document index out of range." << std::endl;
                            break;
                        }
                        doc.data.clear();
                        std::cout << "Enter new key-value pairs (key value). Enter 'done' to finish: ";
                        while (std::cin >> key && key != "done") {
                            std::cin >> value;
                            doc.data[key] = value;
                        }
                        db.updateDocument("user1", collectionName, docIndex, doc);
                        break;
                    case 5:
                        std::cout << "Enter collection name: ";
                        std::cin >> collectionName;
                        if (!collectionExists(db, collectionName)) {
                            std::cout << "Collection not found." << std::endl;
                            break;
                        }
                        std::cout << "Enter document index: ";
                        std::cin >> docIndex;
                        if (docIndex >= db.getDocuments("user1", collectionName).size()) {
                            std::cout << "Document index out of range." << std::endl;
                            break;
                        }
                        db.deleteDocument("user1", collectionName, docIndex);
                        break;
                    case 6:
                        for (const auto& name : db.listCollections("user1")) {
                            std::cout << name << std::endl;
                        }
                        break;
                    case 7:
                        std::cout << "Enter collection name: ";
                        std::cin >> collectionName;
                        if (!collectionExists(db, collectionName)) {
                            std::cout << "Collection not found." << std::endl;
                            break;
                        }
                        for (const auto& d : db.listDocuments("user1", collectionName)) {
                            for (const auto& pair : d.data) {
                                std::cout << pair.first << ": " << pair.second << std::endl;
                            }
                        }
                        break;
                    case 8:
                        std::cout << "Enter collection name: ";
                        std::cin >> collectionName;
                        if (!collectionExists(db, collectionName)) {
                            std::cout << "Collection not found." << std::endl;
                            break;
                        }
                        std::cout << "Enter document index: ";
                        std::cin >> docIndex;
                        if (docIndex >= db.getDocuments("user1", collectionName).size()) {
                            std::cout << "Document index out of range." << std::endl;
                            break;
                        }
                        std::cout << "Enter shift value: ";
                        std::cin >> shift;
                        doc = db.getDocuments("user1", collectionName)[docIndex];
                        encryptDocument(doc, shift);
                        db.updateDocument("user1", collectionName, docIndex, doc);
                        break;
                    case 9:
                        std::cout << "Enter collection name: ";
                        std::cin >> collectionName;
                        if (!collectionExists(db, collectionName)) {
                            std::cout << "Collection not found." << std::endl;
                            break;
                        }
                        std::cout << "Enter document index: ";
                        std::cin >> docIndex;
                        if (docIndex >= db.getDocuments("user1", collectionName).size()) {
                            std::cout << "Document index out of range." << std::endl;
                            break;
                        }
                        std::cout << "Enter shift value: ";
                        std::cin >> shift;
                        doc = db.getDocuments("user1", collectionName)[docIndex];
                        decryptDocument(doc, shift);
                        db.updateDocument("user1", collectionName, docIndex, doc);
                        break;
                    case 10:
                        return 0;
                    default:
                        std::cout << "Invalid choice! Please select a valid option from the menu." << std::endl;
                }
            }
        } else {
            std::cout << "Login failed!" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}


// g++ -o mydatabase main.cpp Database.cpp Encryption.cpp
