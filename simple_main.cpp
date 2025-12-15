#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ============================================
// SIMPLE STUDENT MANAGEMENT SYSTEM
// For C++ Beginners - No OOP!
// ============================================

// Simple structure to store student information
struct Student {
    int id;
    string name;
    int age;
    string major;
    double gpa;
};

// Array to store students (maximum 100 students)
Student students[100];
int studentCount = 0;  // How many students we currently have
const string FILENAME = "students_simple.txt";

// ============================================
// FUNCTION DECLARATIONS
// ============================================
void showMenu();
void addStudent();
void viewAllStudents();
void searchStudent();
void editStudent();
void deleteStudent();
void saveToFile();
void loadFromFile();
int getNextId();
void clearScreen();
void pauseScreen();

// ============================================
// MAIN FUNCTION - Program starts here
// ============================================
int main() {
    loadFromFile();  // Load existing students from file
    
    int choice;
    bool running = true;
    
    while (running) {
        showMenu();
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                editStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 0:
                cout << "\n=== Thank you for using Student Management System! ===\n";
                running = false;
                break;
            default:
                cout << "\n[ERROR] Invalid choice! Please try again.\n";
                pauseScreen();
        }
    }
    
    return 0;
}

// ============================================
// FUNCTION DEFINITIONS
// ============================================

// Display the main menu
void showMenu() {
    clearScreen();
    cout << "\n";
    cout << "========================================\n";
    cout << "   STUDENT MANAGEMENT SYSTEM (SIMPLE)\n";
    cout << "========================================\n";
    cout << "Total Students: " << studentCount << "\n";
    cout << "========================================\n";
    cout << "1. Add New Student\n";
    cout << "2. View All Students\n";
    cout << "3. Search Student by Name\n";
    cout << "4. Edit Student\n";
    cout << "5. Delete Student\n";
    cout << "0. Exit\n";
    cout << "========================================\n";
}

// Add a new student
void addStudent() {
    clearScreen();
    cout << "\n=== ADD NEW STUDENT ===\n\n";
    
    // Check if we have space
    if (studentCount >= 100) {
        cout << "[ERROR] Database is full! Cannot add more students.\n";
        pauseScreen();
        return;
    }
    
    Student newStudent;
    newStudent.id = getNextId();
    
    // Clear the input buffer
    cin.ignore();
    
    // Get student information
    cout << "Student ID (auto-generated): " << newStudent.id << "\n";
    
    cout << "Enter student name: ";
    getline(cin, newStudent.name);
    
    cout << "Enter age: ";
    cin >> newStudent.age;
    
    // Validate age
    if (newStudent.age <= 0 || newStudent.age > 150) {
        cout << "[ERROR] Invalid age! Must be between 1 and 150.\n";
        pauseScreen();
        return;
    }
    
    cin.ignore();  // Clear buffer
    cout << "Enter major: ";
    getline(cin, newStudent.major);
    
    cout << "Enter GPA (0.0 - 4.0): ";
    cin >> newStudent.gpa;
    
    // Validate GPA
    if (newStudent.gpa < 0.0 || newStudent.gpa > 4.0) {
        cout << "[ERROR] Invalid GPA! Must be between 0.0 and 4.0.\n";
        pauseScreen();
        return;
    }
    
    // Add to array
    students[studentCount] = newStudent;
    studentCount++;
    
    // Save to file
    saveToFile();
    
    cout << "\n[SUCCESS] Student added successfully!\n";
    pauseScreen();
}

// View all students
void viewAllStudents() {
    clearScreen();
    cout << "\n=== ALL STUDENTS ===\n\n";
    
    if (studentCount == 0) {
        cout << "[WARNING] No students in the database.\n";
        pauseScreen();
        return;
    }
    
    cout << "Total Students: " << studentCount << "\n\n";
    cout << "------------------------------------------------------------------------------------\n";
    cout << "ID    | Name                     | Age | Major                | GPA  \n";
    cout << "------------------------------------------------------------------------------------\n";
    
    for (int i = 0; i < studentCount; i++) {
        cout << students[i].id << "     | "
             << students[i].name << " | "
             << students[i].age << "  | "
             << students[i].major << " | "
             << students[i].gpa << "\n";
    }
    
    cout << "------------------------------------------------------------------------------------\n";
    pauseScreen();
}

// Search for a student by name
void searchStudent() {
    clearScreen();
    cout << "\n=== SEARCH STUDENT ===\n\n";
    
    if (studentCount == 0) {
        cout << "[WARNING] No students in the database.\n";
        pauseScreen();
        return;
    }
    
    string searchName;
    cin.ignore();
    cout << "Enter student name to search: ";
    getline(cin, searchName);
    
    bool found = false;
    
    cout << "\n=== Search Results ===\n\n";
    
    for (int i = 0; i < studentCount; i++) {
        // Simple search - check if searchName is found in student name
        if (students[i].name.find(searchName) != string::npos) {
            if (!found) {
                cout << "------------------------------------------------------------------------------------\n";
                cout << "ID    | Name                     | Age | Major                | GPA  \n";
                cout << "------------------------------------------------------------------------------------\n";
                found = true;
            }
            
            cout << students[i].id << "     | "
                 << students[i].name << " | "
                 << students[i].age << "  | "
                 << students[i].major << " | "
                 << students[i].gpa << "\n";
        }
    }
    
    if (found) {
        cout << "------------------------------------------------------------------------------------\n";
    } else {
        cout << "[WARNING] No students found matching '" << searchName << "'.\n";
    }
    
    pauseScreen();
}

// Edit a student's information
void editStudent() {
    clearScreen();
    cout << "\n=== EDIT STUDENT ===\n\n";
    
    if (studentCount == 0) {
        cout << "[WARNING] No students in the database.\n";
        pauseScreen();
        return;
    }
    
    int searchId;
    cout << "Enter student ID to edit: ";
    cin >> searchId;
    
    // Find the student
    int index = -1;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == searchId) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        cout << "[ERROR] Student with ID " << searchId << " not found.\n";
        pauseScreen();
        return;
    }
    
    // Display current information
    cout << "\n=== Current Information ===\n";
    cout << "ID: " << students[index].id << "\n";
    cout << "Name: " << students[index].name << "\n";
    cout << "Age: " << students[index].age << "\n";
    cout << "Major: " << students[index].major << "\n";
    cout << "GPA: " << students[index].gpa << "\n\n";
    
    // Get new information
    cin.ignore();
    
    cout << "=== Enter New Information ===\n";
    cout << "New name: ";
    getline(cin, students[index].name);
    
    cout << "New age: ";
    cin >> students[index].age;
    
    if (students[index].age <= 0 || students[index].age > 150) {
        cout << "[ERROR] Invalid age!\n";
        pauseScreen();
        return;
    }
    
    cin.ignore();
    cout << "New major: ";
    getline(cin, students[index].major);
    
    cout << "New GPA (0.0 - 4.0): ";
    cin >> students[index].gpa;
    
    if (students[index].gpa < 0.0 || students[index].gpa > 4.0) {
        cout << "[ERROR] Invalid GPA!\n";
        pauseScreen();
        return;
    }
    
    // Save to file
    saveToFile();
    
    cout << "\n[SUCCESS] Student information updated successfully!\n";
    pauseScreen();
}

// Delete a student
void deleteStudent() {
    clearScreen();
    cout << "\n=== DELETE STUDENT ===\n\n";
    
    if (studentCount == 0) {
        cout << "[WARNING] No students in the database.\n";
        pauseScreen();
        return;
    }
    
    int searchId;
    cout << "Enter student ID to delete: ";
    cin >> searchId;
    
    // Find the student
    int index = -1;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == searchId) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        cout << "[ERROR] Student with ID " << searchId << " not found.\n";
        pauseScreen();
        return;
    }
    
    // Display student information
    cout << "\n=== Student to Delete ===\n";
    cout << "ID: " << students[index].id << "\n";
    cout << "Name: " << students[index].name << "\n";
    cout << "Age: " << students[index].age << "\n";
    cout << "Major: " << students[index].major << "\n";
    cout << "GPA: " << students[index].gpa << "\n\n";
    
    // Confirm deletion
    char confirm;
    cout << "Are you sure you want to delete this student? (y/n): ";
    cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        // Shift all students after this one to the left
        for (int i = index; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }
        studentCount--;
        
        // Save to file
        saveToFile();
        
        cout << "\n[SUCCESS] Student deleted successfully!\n";
    } else {
        cout << "\n[INFO] Deletion cancelled.\n";
    }
    
    pauseScreen();
}

// Save all students to file
void saveToFile() {
    ofstream file(FILENAME);
    
    if (!file.is_open()) {
        cout << "[ERROR] Could not save to file!\n";
        return;
    }
    
    // Write number of students
    file << studentCount << "\n";
    
    // Write each student (one per line, fields separated by '|')
    for (int i = 0; i < studentCount; i++) {
        file << students[i].id << "|"
             << students[i].name << "|"
             << students[i].age << "|"
             << students[i].major << "|"
             << students[i].gpa << "\n";
    }
    
    file.close();
}

// Load all students from file
void loadFromFile() {
    ifstream file(FILENAME);
    
    if (!file.is_open()) {
        // File doesn't exist yet, that's okay
        return;
    }
    
    // Read number of students
    file >> studentCount;
    file.ignore();  // Skip newline
    
    // Read each student
    for (int i = 0; i < studentCount; i++) {
        string line;
        getline(file, line);
        
        // Parse the line (fields separated by '|')
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        size_t pos4 = line.find('|', pos3 + 1);
        
        students[i].id = stoi(line.substr(0, pos1));
        students[i].name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        students[i].age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        students[i].major = line.substr(pos3 + 1, pos4 - pos3 - 1);
        students[i].gpa = stod(line.substr(pos4 + 1));
    }
    
    file.close();
}

// Get the next available student ID
int getNextId() {
    if (studentCount == 0) {
        return 1;
    }
    
    int maxId = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id > maxId) {
            maxId = students[i].id;
        }
    }
    
    return maxId + 1;
}

// Clear the screen
void clearScreen() {
    // For Windows
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Pause and wait for user input
void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}
