//
// Created by Gor on 30/05/2023.
//
/**
 * @file PasswordEntry.cpp
 * @brief Implementacja metod klasy PasswordEntry
 * @author Gor
 * @date 30/05/2023
 */
#include "PasswordEntry.h"

/**
 * @brief Konstruktor klasy PasswordEntry
 * @param name Nazwa hasła
 * @param password Samo hasło
 * @param category Kategoria hasła
 * @param webService Opcjonalny parametr reprezentujący serwis internetowy
 * @param login Opcjonalny parametr reprezentujący login
 *
 */
PasswordEntry::PasswordEntry() : name(""), password(""), category("") {}

PasswordEntry::PasswordEntry(const std::string& name, const std::string& password, const std::string& category,
                             const std::string& webService, const std::string& login)
        : name(name), password(password), category(category), webService(webService), login(login) {}

/**
 * @brief Getter dla nazwy hasła
 * @return Nazwa hasła
 */
std::string PasswordEntry::getName() const {
    return name;
}

/**
 * @brief Getter dla hasła
 * @return Hasło
 */
std::string PasswordEntry::getPassword() const {
    return password;
}

/**
 * @brief Getter dla kategorii hasła
 * @return Kategoria hasła
 */
std::string PasswordEntry::getCategory() const {
    return category;
}

/**
 * @brief Getter dla serwisu internetowego
 * @return Serwis internetowy
 */
std::string PasswordEntry::getWebService() const {
    return webService;
}

/**
 * @brief Getter dla loginu
 * @return Login
 */
std::string PasswordEntry::getLogin() const {
    return login;
}

/**
 * @brief Sprawdza, czy hasło posiada opcjonalne dane
 * @return True, jeśli hasło posiada opcjonalne dane, false w przeciwnym wypadku
 */
bool PasswordEntry::hasOptionalData() const {
    return !webService.empty() || !login.empty();
}

void PasswordEntry::setName(const std::string &name) {
    PasswordEntry::name = name;
}

void PasswordEntry::setPassword(const std::string &password) {
    PasswordEntry::password = password;
}

void PasswordEntry::setCategory(const std::string &category) {
    PasswordEntry::category = category;
}

void PasswordEntry::setWebService(const std::string &webService) {
    PasswordEntry::webService = webService;
}

void PasswordEntry::setLogin(const std::string &login) {
    PasswordEntry::login = login;
}
