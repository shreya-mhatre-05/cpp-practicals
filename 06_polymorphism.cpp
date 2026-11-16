// Practical 06: Runtime Polymorphism and Abstract Classes
// Shape is an ABSTRACT class (it has a pure virtual function).
// Circle, Rectangle and Triangle each provide their own area().
// A Shape pointer calls the correct area() at RUNTIME.

#include <iostream>
#include <memory>    // unique_ptr
#include <vector>
#include <string>
#include <cmath>     // M_PI is not guaranteed, so we define our own PI below
using namespace std;

const double PI = 3.14159265358979323846;

// ---------------------------------------------------------------
// ABSTRACT BASE CLASS
// ---------------------------------------------------------------
class Shape {
public:
    // PURE VIRTUAL function ("= 0"): no body here. Every derived class MUST
    // provide its own area(). A class with a pure virtual function is
    // ABSTRACT, so you cannot create a Shape object directly.
    virtual double area() const = 0;

    virtual string name() const = 0;

    // VIRTUAL DESTRUCTOR: so that deleting a derived object through a
    // Shape pointer runs the derived destructor too (no leak, no undefined
    // behaviour).
    virtual ~Shape() {
        cout << "  [Shape destructor]\n";
    }
};

// ---------------------------------------------------------------
// DERIVED CLASSES
// ---------------------------------------------------------------
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override { return PI * radius * radius; }
    string name() const override { return "Circle"; }
    ~Circle() { cout << "  [Circle destructor]\n"; }
};

class Rectangle : public Shape {
private:
    double length, width;
public:
    Rectangle(double l, double w) : length(l), width(w) {}
    double area() const override { return length * width; }
    string name() const override { return "Rectangle"; }
    ~Rectangle() { cout << "  [Rectangle destructor]\n"; }
};

class Triangle : public Shape {
private:
    double base, height;
public:
    Triangle(double b, double h) : base(b), height(h) {}
    double area() const override { return 0.5 * base * height; }
    string name() const override { return "Triangle"; }
    ~Triangle() { cout << "  [Triangle destructor]\n"; }
};

// A function that works with ANY shape. It only knows about Shape,
// yet the correct area() is called for each real object.
void printArea(const Shape& s) {
    cout << "  " << s.name() << " area = " << s.area() << "\n";
}

int main() {
    cout << "=== 1. Shapes stored as Shape pointers ===\n";

    // A vector of base-class pointers holding different derived objects.
    // unique_ptr frees each object automatically (practical 04).
    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Circle>(5.0));
    shapes.push_back(make_unique<Rectangle>(4.0, 6.0));
    shapes.push_back(make_unique<Triangle>(3.0, 8.0));

    // Same call s->area(), but a DIFFERENT function runs for each object.
    for (const auto& s : shapes) {
        cout << "  " << s->name() << " area = " << s->area() << "\n";
    }

    cout << "\n=== 2. Using a base-class reference ===\n";
    Circle c(2.5);
    Rectangle r(10.0, 3.5);
    printArea(c);
    printArea(r);

    cout << "\n=== 3. Why Shape cannot be created ===\n";
    cout << "  Shape s;  // ERROR: cannot create an object of an abstract class\n";
    // Shape s;       // Uncomment this line to see the compiler error.

    cout << "\n=== End of main: objects are destroyed ===\n";
    return 0;
}