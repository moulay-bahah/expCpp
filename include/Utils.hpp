#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iostream>

namespace Color {
    // ANSI color codes for cross-platform terminal coloring
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";
    const std::string BOLD = "\033[1m";
    const std::string UNDERLINE = "\033[4m";
}

namespace Utils {
    // Clear the console screen
    void clearScreen();
    
    // Print a formatted header
    void printHeader(const std::string& text);
    
    // Print an error message
    void printError(const std::string& message);
    
    // Print a success message
    void printSuccess(const std::string& message);
    
    // Print a warning message
    void printWarning(const std::string& message);
    
    // Print a separator line
    void printSeparator();
    
    // Get validated integer input
    int getIntInput(const std::string& prompt);
    
    // Get validated double input
    double getDoubleInput(const std::string& prompt);
    
    // Get string input (with trimming)
    std::string getStringInput(const std::string& prompt);
    
    // Trim whitespace from string
    std::string trim(const std::string& str);
    
    // Pause and wait for user to press Enter
    void pause();
}

#endif // UTILS_HPP
