// Practical 01: C++ Fundamentals
// Demonstrates data types, constants, variables, operators and input/output.

#include <iostream>
#include <string>
using namespace std;

int main() {
    // A constant: its value cannot change after it is set
    const int PASS_MARK = 40;

    // Variables of different data types
    string name;                 // text
    int marks1, marks2, marks3;  // whole numbers
    int total;
    double average;              // decimal number
    char grade;                  // single character
    bool isPass;                 // true / false

    // Input using cin
    cout << "Enter student name: ";
    getline(cin, name);
    cout << "Enter marks in 3 subjects (out of 100): ";
    cin >> marks1 >> marks2 >> marks3;

    // Arithmetic operators
    total = marks1 + marks2 + marks3;
    average = total / 3.0;

    // Relational + logical operators
    // Pass only if every subject is at or above the pass mark
    isPass = (marks1 >= PASS_MARK) && (marks2 >= PASS_MARK) && (marks3 >= PASS_MARK);

    if (average >= 75)             grade = 'A';
    else if (average >= 60)        grade = 'B';
    else if (average >= PASS_MARK) grade = 'C';
    else                           grade = 'F';

    // Output using cout
    cout << "\n----- Result -----\n";
    cout << "Name    : " << name << endl;
    cout << "Total   : " << total << " / 300" << endl;
    cout << "Average : " << average << endl;
    cout << "Grade   : " << grade << endl;
    cout << "Status  : " << (isPass ? "PASS" : "FAIL") << endl;

    // Remainder operator example
    cout << "Total % 7 = " << total % 7 << endl;

    return 0;
}