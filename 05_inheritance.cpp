// Practical 05: Single and Multilevel Inheritance
// University management example:  Person -> Student -> GraduateStudent
//
//   Person            (base class: name, age)
//     |
//   Student           (derived from Person: studentId, course)
//     |
//   GraduateStudent   (derived from Student: researchTopic, supervisor)
//
// Person -> Student                    is SINGLE inheritance.
// Person -> Student -> GraduateStudent is MULTILEVEL inheritance.

#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------------------------
// BASE CLASS: Person
// ---------------------------------------------------------------
class Person {
private:
    int age;                 // private: NOT accessible in derived classes directly
protected:
    string name;             // protected: accessible in derived classes, hidden outside
public:
    Person(const string& n, int a) : age(a), name(n) {
        cout << "  [Person constructor] " << name << "\n";
    }
    ~Person() {
        cout << "  [Person destructor] " << name << "\n";
    }

    int getAge() const { return age; }    // derived classes use this to read age

    void display() const {
        cout << "  Name : " << name << "\n";
        cout << "  Age  : " << age << "\n";
    }
};

// ---------------------------------------------------------------
// DERIVED CLASS (single inheritance): Student is-a Person
// ---------------------------------------------------------------
class Student : public Person {
private:
    int studentId;
protected:
    string course;           // protected so GraduateStudent can use it
public:
    // The base class constructor is called FIRST, using the initializer list.
    Student(const string& n, int a, int id, const string& c)
        : Person(n, a), studentId(id), course(c) {
        cout << "  [Student constructor] ID " << studentId << "\n";
    }
    ~Student() {
        cout << "  [Student destructor] ID " << studentId << "\n";
    }

    int getStudentId() const { return studentId; }

    void display() const {
        Person::display();                       // reuse the base class display
        cout << "  ID   : " << studentId << "\n";
        cout << "  Course: " << course << "\n";
    }
};

// ---------------------------------------------------------------
// DERIVED CLASS (multilevel inheritance): GraduateStudent is-a Student
// ---------------------------------------------------------------
class GraduateStudent : public Student {
private:
    string researchTopic;
    string supervisor;
public:
    GraduateStudent(const string& n, int a, int id, const string& c,
                    const string& topic, const string& sup)
        : Student(n, a, id, c), researchTopic(topic), supervisor(sup) {
        cout << "  [GraduateStudent constructor] " << researchTopic << "\n";
    }
    ~GraduateStudent() {
        cout << "  [GraduateStudent destructor] " << researchTopic << "\n";
    }

    void display() const {
        Student::display();                      // reuse Student (and Person) display
        cout << "  Research  : " << researchTopic << "\n";
        cout << "  Supervisor: " << supervisor << "\n";
    }

    // Shows which inherited members this class can reach
    void showAccess() const {
        cout << "  Inside GraduateStudent, we can use:\n";
        cout << "    name (protected in Person)    = " << name << "\n";
        cout << "    course (protected in Student) = " << course << "\n";
        cout << "    getAge() (public in Person)   = " << getAge() << "\n";
        cout << "    getStudentId() (public)       = " << getStudentId() << "\n";
        // cout << getAge_private;  // age is PRIVATE in Person, so no direct access
    }
};

int main() {
    cout << "=== 1. Person object ===\n";
    Person p("Anita Sharma", 45);
    p.display();

    cout << "\n=== 2. Student object (single inheritance) ===\n";
    Student s("Rahul Patil", 20, 1001, "B.Sc. Computer Science");
    s.display();
    cout << "  Age through inherited getAge(): " << s.getAge() << "\n";

    cout << "\n=== 3. GraduateStudent object (multilevel inheritance) ===\n";
    GraduateStudent g("Shreya Mhatre", 24, 2001, "M.Sc. Computer Science",
                      "Machine Learning in Healthcare", "Dr. Kulkarni");
    g.display();
    cout << "\n";
    g.showAccess();

    cout << "\n=== End of main: destructors run in reverse order ===\n";
    return 0;
}