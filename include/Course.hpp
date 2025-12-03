#ifndef COURSE_HPP
#define COURSE_HPP

#include <string>

class Course {
private:
    std::string courseCode;
    std::string courseName;
    int credits;
    std::string instructor;

public:
    // Constructors
    Course();
    Course(const std::string& code, const std::string& name, int credits, const std::string& instructor);
    
    // Getters
    std::string getCourseCode() const { return courseCode; }
    std::string getCourseName() const { return courseName; }
    int getCredits() const { return credits; }
    std::string getInstructor() const { return instructor; }
    
    // Setters
    void setCourseCode(const std::string& code);
    void setCourseName(const std::string& name);
    void setCredits(int credits);
    void setInstructor(const std::string& instructor);
    
    // Display
    void display() const;
};

#endif // COURSE_HPP
