#include <iostream>
#include <filesystem>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include "PasswordManager.h"
#include "SimpleCipher.h"

void hideTimestampInFile(const std::string& filePath) {
    std::fstream file(filePath, std::ios::in);

    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku.\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    file.close();

    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    // Ensure there is enough space in lines vector
    while(lines.size() < 33) {
        lines.push_back("");
    }

    if (!lines[10].empty()) {
        lines[10] += ", ";
    }
    lines[10] += std::to_string(localTime->tm_hour);

    if (!lines[20].empty()) {
        lines[20] += ", ";
    }
    lines[20] += std::to_string(localTime->tm_min);

    if (!lines[31].empty()) {
        lines[31] += ", ";
    }
    lines[31] += std::to_string(localTime->tm_sec);

    file.open(filePath, std::ios::out);

    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku.\n";
        return;
    }

    for (const std::string& line : lines) {
        file << line << "\n";
    }

    file.close();
}


int main() {

    hideTimestampInFile("/Users/Gor/CLionProjects/s27734/Test");

    std::string filePath;
    std::cout << "Podaj nazwę pliku z listy lub pełną ścieżkę do pliku:\n";
    std::getline(std::cin, filePath);


    PasswordManager manager;
    char choice;

    while(true) {
        std::cout << "\n----MENU----\n";
        std::cout << "1. Dodaj hasło\n";
        std::cout << "2. Edytuj hasło\n";
        std::cout << "3. Usuń hasło\n";
        std::cout << "4. Wyszukaj hasło\n";
        std::cout << "5. Dodaj kategorię\n";
        std::cout << "6. Usuń kategorię\n";
        std::cout << "7. Odszyfruj wszyskie hasla\n";
        std::cout << "8. Wyjdz z programu\n";
        std::cout << "Wybierz opcję: ";
        std::cin >> choice;
        std::cin.ignore();

        switch(choice) {
            case '1':
                manager.addPassword();
                manager.savePasswordsToFile("/Users/Gor/CLionProjects/s27734/Test");
                hideTimestampInFile("/Users/Gor/CLionProjects/s27734/Test");
                break;
            case '2':
                manager.editPassword();
                hideTimestampInFile("/Users/Gor/CLionProjects/s27734/Test");

                break;
            case '3':
                manager.removePassword();
                hideTimestampInFile("/Users/Gor/CLionProjects/s27734/Test");

                break;
            case '4':
                std::cout << "Search by:\n"
                          << "1. Name\n"
                          << "2. Category\n";
                int searchOption;
                std::cin >> searchOption;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (searchOption == 1) {
                    std::string name;
                    std::cout << "Enter the name: ";
                    std::getline(std::cin, name);
                    manager.printPasswords(manager.searchPasswordsByName(name));
                } else if (searchOption == 2) {
                    std::string category;
                    std::cout << "Enter the category: ";
                    std::getline(std::cin, category);
                    manager.printPasswords(manager.searchPasswordsByCategory(category));
                } else {
                    std::cout << "Invalid option. Please try again.\n";
                }
                break;
            case '5':
                manager.addCategory();
                hideTimestampInFile("/Users/Gor/CLionProjects/s27734/Test");

                break;
            case '6':
                manager.removeCategory();
                hideTimestampInFile("/Users/Gor/CLionProjects/s27734/Test");

                break;
            case '7':
                manager.decryptAllPasswords();
                hideTimestampInFile("/Users/Gor/CLionProjects/s27734/Test");

                break;
            case '8':
                std::cout << "Dziekuje za korzystanie z programu!\n";
                return 0;
            default:
                std::cout << "Nieznana opcja. Spróbuj ponownie.\n";
        }
    }



    return 0;

}
//                std::cout << "Dziękujemy za skorzystanie z programu!\n";