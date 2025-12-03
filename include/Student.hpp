#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
#include <vector>
#include <iostream>

class Student {
private:
    int id;
    std::string name;
    int age;
    std::string major;
    double gpa;

public:
    // Constructors
    Student();
    Student(int id, const std::string& name, int age, const std::string& major, double gpa);
    
    // Getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    int getAge() const { return age; }
    std::string getMajor() const { return major; }
    double getGpa() const { return gpa; }
    
    // Setters with validation
    void setId(int id);
    void setName(const std::string& name);
    void setAge(int age);
    void setMajor(const std::string& major);
    void setGpa(double gpa);
    
    // Display student information
    void display() const;
    void displayDetailed() const;
    
    // Comparison operators for sorting
    bool operator<(const Student& other) const; // Sort by name
    bool operator>(const Student& other) const;
    
    // JSON serialization
    std::string toJson() const;
    static Student fromJson(const std::string& json);
    
    // Validation
    static bool isValidGpa(double gpa);
    static bool isValidAge(int age);
};

#endif // STUDENT_HPP
