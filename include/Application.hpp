#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Database.hpp"

class Application {
private:
    Database database;
    bool running;
    
    // Menu display methods
    void displayMainMenu() const;
    void displaySearchMenu() const;
    void displaySortMenu() const;
    
    // Menu handlers
    void handleMainMenu();
    void handleAddStudent();
    void handleEditStudent();
    void handleDeleteStudent();
    void handleSearch();
    void handleSort();
    void handleListAll();
    void handleStatistics();
    void handleExport();

public:
    // Constructor
    Application();
    
    // Main application loop
    void run();
    
    // Exit application
    void exit();
};

#endif // APPLICATION_HPP
