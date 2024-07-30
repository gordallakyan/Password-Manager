#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include "iostream"
#include "map"
#include "vector"
#include "PasswordEntry.h"
class PasswordManager {
private:
    std::vector<PasswordEntry> passwords;
    std::vector<std::string> categories;

public:
    PasswordManager();
    void displayCategories();
    std::vector<PasswordEntry> searchPasswordsByName(const std::string &name);
    std::vector<PasswordEntry> searchPasswordsByCategory(const std::string &category);
    void printPasswords(const std::vector<PasswordEntry> &passwords);
    std::vector<PasswordEntry> sortPasswords();
    void printCategories();
    void addPassword();
    void editPassword();
    void removePassword();
    void addCategory();
    void removeCategory();
    void decryptAllPasswords();
    void savePasswordsToFile(const std::string &filename);

    void loadPasswordsFromFile(const std::string &filename);
};

#endif  // PASSWORD_MANAGER_H
