#ifndef PASSWORD_MANAGER_PASSWORDENTRY_H
#define PASSWORD_MANAGER_PASSWORDENTRY_H

#include "string"

class PasswordEntry {
private:
    std::string name;
    std::string password;
    std::string category;
    std::string webService;
    std::string login;
public:
    PasswordEntry();
    PasswordEntry(const std::string& name, const std::string& password, const std::string& category, const std::string& webService = "", const std::string& login = "");
    std::string getName() const;
    std::string getPassword() const;
    std::string getCategory() const;
    std::string getWebService() const;
    std::string getLogin() const;
    bool hasOptionalData() const;

    void setName(const std::string &name);
    void setPassword(const std::string &password);
    void setCategory(const std::string &category);
    void setWebService(const std::string &webService);
    void setLogin(const std::string &login);
};

#endif //PASSWORD_MANAGER_PASSWORDENTRY_H
