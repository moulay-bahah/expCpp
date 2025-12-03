#include "../include/Application.hpp"
#include "../include/Utils.hpp"
#include <iostream>
#include <exception>

#ifdef _WIN32
    #include <windows.h>
    
    // Enable ANSI escape codes on Windows 10+
    void enableAnsiColors() {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }
#endif

int main() {
    try {
#ifdef _WIN32
        // Enable ANSI colors on Windows
        enableAnsiColors();
#endif
        
        Application app;
        app.run();
        
        return 0;
        
    } catch (const std::exception& e) {
        Utils::printError(std::string("Fatal error: ") + e.what());
        return 1;
    } catch (...) {
        Utils::printError("Unknown fatal error occurred.");
        return 1;
    }
}
