#include "../include/Utils.hpp"
#include <limits>
#include <algorithm>
#include <sstream>

#ifdef _WIN32
    #include <windows.h>
#endif

namespace Utils {

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printHeader(const std::string& text) {
    std::cout << "\n" << Color::BOLD << Color::CYAN 
              << "╔══════════════════════════════════════════════════════════════╗\n"
              << "║  " << text;
    
    // Pad to align properly
    int padding = 57 - text.length();
    for (int i = 0; i < padding; i++) std::cout << " ";
    
    std::cout << "║\n"
              << "╔══════════════════════════════════════════════════════════════╗"
              << Color::RESET << "\n\n";
}

void printError(const std::string& message) {
    std::cout << Color::RED << "✖ Error: " << message << Color::RESET << "\n";
}

void printSuccess(const std::string& message) {
    std::cout << Color::GREEN << "✓ " << message << Color::RESET << "\n";
}

void printWarning(const std::string& message) {
    std::cout << Color::YELLOW << "⚠ Warning: " << message << Color::RESET << "\n";
}

void printSeparator() {
    std::cout << Color::CYAN << "────────────────────────────────────────────────────────────────" 
              << Color::RESET << "\n";
}

int getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << Color::YELLOW << prompt << Color::RESET;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printError("Invalid input. Please enter a valid integer.");
        }
    }
}

double getDoubleInput(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << Color::YELLOW << prompt << Color::RESET;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printError("Invalid input. Please enter a valid number.");
        }
    }
}

std::string getStringInput(const std::string& prompt) {
    std::string input;
    std::cout << Color::YELLOW << prompt << Color::RESET;
    std::getline(std::cin, input);
    return trim(input);
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

void pause() {
    std::cout << Color::CYAN << "\nPress Enter to continue..." << Color::RESET;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

} // namespace Utils
