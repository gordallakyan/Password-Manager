#include "PasswordManager.h"
#include "SimpleCipher.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include "PasswordEntry.h"
#include "SimpleCipher.h"
/// Konstruktor domyślny
PasswordManager::PasswordManager() {}

/// @brief Metoda wyszukująca hasła według nazwy
/// @param name Nazwa szukanego hasła
/// @return Vector z hasłami pasującymi do podanej nazwy
std::vector<PasswordEntry> PasswordManager::searchPasswordsByName(const std::string &name) {
    std::vector<PasswordEntry> results;
    for (const PasswordEntry &entry: passwords) {
        if (entry.getName() == name) {
            results.push_back(entry);
        }
    }
    return results;
}

/// @brief Metoda wyszukująca hasła według kategorii
/// @param category Kategoria szukanego hasła
/// @return Vector z hasłami pasującymi do podanej kategorii
std::vector<PasswordEntry> PasswordManager::searchPasswordsByCategory(const std::string &category) {
    std::vector<PasswordEntry> results;
    for (const PasswordEntry &entry: passwords) {
        if (entry.getCategory() == category) {
            results.push_back(entry);
        }
    }
    return results;
}

/// @brief Metoda wyświetlająca hasła
/// @param passwords Vector z hasłami do wyświetlenia
void PasswordManager::printPasswords(const std::vector<PasswordEntry> &passwords) {
    for (const PasswordEntry &entry: passwords) {
        std::cout << "Nazwa: " << entry.getName() << ", Kategoria: " << entry.getCategory() << ", Hasło: "
                  << entry.getPassword() << "\n";
    }
}


/// @brief Metoda dodająca nowe hasło
void PasswordManager::addPassword() {
    PasswordEntry newEntry;
    std::string input;

    std::cout << "Podaj nazwę dla nowego hasła: ";
    std::cin >> input;
    newEntry.setName(input);

    std::cout << "Podaj kategorię dla nowego hasła: ";
    std::cin >> input;
    newEntry.setCategory(input);

    std::cout << "Podaj nowe hasło: ";
    std::cin >> input;
    newEntry.setPassword(input);
    SimpleCipher simpleCipher;
    input = simpleCipher.encrypt(input);
    newEntry.setPassword(input);
    passwords.push_back(newEntry);
    std::cout << "Hasło dodane pomyślnie.\n";



}

/// @brief Metoda edytująca istniejące hasło
void PasswordManager::editPassword() {
    std::string name;
    std::cout << "Podaj nazwę hasła do edycji: ";
    std::cin >> name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (PasswordEntry& entry : passwords) {
        if (entry.getName() == name) {
            std::cout << "Podaj nową nazwę dla hasła: ";
            std::cin >> name;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            entry.setName(name);

            std::cout << "Podaj nową kategorię dla hasła: ";
            std::cin >> name;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            entry.setCategory(name);

            std::cout << "Podaj nowe hasło: ";
            std::cin >> name;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            entry.setPassword(name);
            SimpleCipher simpleCipher;
            simpleCipher.encrypt(name);

            std::cout << "Hasło zaktualizowane pomyślnie.\n";
            return;
        }
    }

    std::cout << "Nie znaleziono hasła o nazwie " << name << ".\n";
}


/// @brief Metoda usuwająca istniejące hasło
void PasswordManager::removePassword() {
    std::string name;
    std::cout << "Podaj nazwę hasła do usunięcia: ";
    std::cin >> name;

    for (auto it = passwords.begin(); it != passwords.end(); ++it) {
        if (it->getName() == name) {
            passwords.erase(it);
            std::cout << "Hasło zostało usunięte.\n";
            savePasswordsToFile("/Users/Gor/CLionProjects/s27734/Test"); // update file after removing password
            return;
        }
    }

    std::cout << "Nie znaleziono hasła o nazwie " << name << ".\n";
}


/// @brief Metoda dodająca nową kategorię
void PasswordManager::addCategory() {
    std::string category;
    std::cout << "Podaj nazwę kategorii, którą chcesz dodać: ";
    std::getline(std::cin, category);

    for (const auto &existingCategory : categories) {
        if (existingCategory == category) {
            std::cout << "Kategoria \"" << category << "\" już istnieje.\n";
            return;
        }
    }

    categories.push_back(category);
    std::cout << "Kategoria \"" << category << "\" została dodana.\n";
}

void PasswordManager::decryptAllPasswords() {
    SimpleCipher simpleCipher;
    for (PasswordEntry& entry : passwords) {
        std::string decryptedPassword = simpleCipher.decrypt(entry.getPassword());
        entry.setPassword(decryptedPassword);
    }
    std::cout << "Wszystkie hasła zostały odszyfrowane.\n";

    savePasswordsToFile("/Users/Gor/CLionProjects/s27734/Test"); // replace with your file path
}



/// @brief Metoda usuwająca istniejącą kategorię
void PasswordManager::removeCategory() {
    std::string category;
    std::cout << "Podaj nazwę kategorii, którą chcesz usunąć: ";
    std::getline(std::cin, category);

    auto cat_it = std::find(categories.begin(), categories.end(), category);
    if (cat_it != categories.end()) {
        categories.erase(cat_it);
        std::cout << "Kategoria \"" << category << "\" została usunięta.\n";
    } else {
        std::cout << "Nie znaleziono kategorii o nazwie \"" << category << "\".\n";
    }

    passwords.erase(std::remove_if(passwords.begin(), passwords.end(),
                                   [&](PasswordEntry &passwordEntry) {
                                       return passwordEntry.getCategory() == category;
                                   }),
                    passwords.end());


}
void PasswordManager::savePasswordsToFile(const std::string &filename) {
    std::ofstream outFile(filename, std::ios::out | std::ios::trunc);
    if (!outFile.is_open()) {
        std::cout << "Błąd przy otwieraniu pliku do zapisu: " << filename << "\n";
        return;
    }

    for (const PasswordEntry &entry : passwords) {
        outFile << entry.getName() << ","
                << entry.getCategory() << ","
                << entry.getPassword() << "\n";
    }

    outFile.close();
    std::cout << "Zapisano hasła do pliku: " << filename << "\n";
}
void PasswordManager::loadPasswordsFromFile(const std::string &filename) {
    std::ifstream inFile(filename, std::ios::in);
    if (!inFile.is_open()) {
        std::cout << "Błąd przy otwieraniu pliku do odczytu: " << filename << "\n";
        return;
    }

    passwords.clear();
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string name, category, password;
        std::getline(ss, name, ',');
        std::getline(ss, category, ',');
        std::getline(ss, password, ',');
        passwords.push_back(PasswordEntry(name, password, category));
    }

    inFile.close();
    std::cout << "Wczytano hasła z pliku: " << filename << "\n";
}