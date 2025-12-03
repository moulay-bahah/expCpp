#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "Student.hpp"
#include <vector>
#include <string>
#include <map>

class Database {
private:
    std::vector<Student> students;
    std::string filename;
    
    // Helper methods
    int generateNextId() const;

public:
    // Constructor
    explicit Database(const std::string& filename = "students.json");
    
    // File I/O
    void loadFromFile();
    void saveToFile() const;
    
    // CRUD Operations
    void addStudent(const Student& student);
    void addStudentInteractive();
    bool editStudent(int id);
    bool deleteStudent(int id);
    
    // Search operations
    std::vector<Student> searchById(int id) const;
    std::vector<Student> searchByName(const std::string& name) const;
    std::vector<Student> searchByMajor(const std::string& major) const;
    std::vector<Student> searchByGpaRange(double minGpa, double maxGpa) const;
    
    // Display all students
    void displayAll() const;
    void displayStudents(const std::vector<Student>& studentList) const;
    
    // Sorting
    void sortByName(bool ascending = true);
    void sortByGpa(bool ascending = true);
    
    // Statistics
    double getAverageGpa() const;
    double getHighestGpa() const;
    std::map<std::string, int> getStudentsPerMajor() const;
    void displayStatistics() const;
    
    // Export
    void exportReport(const std::string& filename) const;
    
    // Utility
    int getStudentCount() const { return students.size(); }
    bool isEmpty() const { return students.empty(); }
};

#endif // DATABASE_HPP
