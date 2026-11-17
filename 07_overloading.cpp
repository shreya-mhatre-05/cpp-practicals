// Practical 07: Compile-Time Polymorphism - Function and Operator Overloading
// The compiler picks the correct version at COMPILE TIME, based on the
// number and types of the arguments (or the types of the operands).

#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------------------------
// PART 1: FUNCTION OVERLOADING
// Same name "add", different parameter lists.
// ---------------------------------------------------------------
int add(int a, int b) {
    cout << "  [add(int, int)] ";
    return a + b;
}

double add(double a, double b) {
    cout << "  [add(double, double)] ";
    return a + b;
}

int add(int a, int b, int c) {
    cout << "  [add(int, int, int)] ";
    return a + b + c;
}

string add(const string& a, const string& b) {
    cout << "  [add(string, string)] ";
    return a + b;
}

// ---------------------------------------------------------------
// PART 2: OPERATOR OVERLOADING with a ComplexNumber class
// ---------------------------------------------------------------
class ComplexNumber {
private:
    double real;
    double imag;
public:
    ComplexNumber(double r = 0, double i = 0) : real(r), imag(i) {}

    // Overloaded + : (a+bi) + (c+di) = (a+c) + (b+d)i
    ComplexNumber operator+(const ComplexNumber& other) const {
        return ComplexNumber(real + other.real, imag + other.imag);
    }

    // Overloaded - : (a+bi) - (c+di) = (a-c) + (b-d)i
    ComplexNumber operator-(const ComplexNumber& other) const {
        return ComplexNumber(real - other.real, imag - other.imag);
    }

    // Overloaded == : two complex numbers are equal if both parts match
    bool operator==(const ComplexNumber& other) const {
        return real == other.real && imag == other.imag;
    }

    // Overloaded << so that cout can print a ComplexNumber directly.
    // It is a friend because it needs to read the private members.
    friend ostream& operator<<(ostream& os, const ComplexNumber& c) {
        os << c.real << (c.imag < 0 ? " - " : " + ")
           << (c.imag < 0 ? -c.imag : c.imag) << "i";
        return os;
    }
};

int main() {
    cout << "=== 1. Function overloading ===\n";
    cout << add(5, 3) << "\n";                       // picks add(int, int)
    cout << add(2.5, 3.7) << "\n";                   // picks add(double, double)
    cout << add(1, 2, 3) << "\n";                    // picks add(int, int, int)
    cout << add(string("Hello, "), string("C++")) << "\n";   // picks add(string, string)

    cout << "\n=== 2. Operator overloading (ComplexNumber) ===\n";
    ComplexNumber c1(3, 4);
    ComplexNumber c2(1, -2);
    cout << "  c1 = " << c1 << "\n";
    cout << "  c2 = " << c2 << "\n";
    cout << "  c1 + c2 = " << (c1 + c2) << "\n";
    cout << "  c1 - c2 = " << (c1 - c2) << "\n";

    cout << "\n=== 3. Test cases for the overloaded operators ===\n";
    ComplexNumber zero;
    cout << "  c1 + zero = " << (c1 + zero) << "  (adding zero changes nothing)\n";
    cout << "  (c1 + c2) == ComplexNumber(4, 2) ? "
         << ((c1 + c2) == ComplexNumber(4, 2) ? "true" : "false") << "\n";
    cout << "  c1 == c2 ? " << (c1 == c2 ? "true" : "false") << "\n";

    return 0;
}
