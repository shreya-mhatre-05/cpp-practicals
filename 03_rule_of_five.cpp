// Practical 03: Constructors and the Rule of Five
// IntArray owns a dynamically allocated array of integers.
// Because it owns a resource, it needs all five special member functions.

#include <iostream>
#include <utility>   // std::move
using namespace std;

class IntArray {
private:
    int* data;      // pointer to the owned array on the heap
    int size;       // number of elements

public:
    // 1. DEFAULT CONSTRUCTOR: creates an empty array (no memory owned).
    IntArray() : data(nullptr), size(0) {
        cout << "[Default constructor]\n";
    }

    // 2. PARAMETERIZED CONSTRUCTOR: allocates 'n' ints and fills them with 'value'.
    IntArray(int n, int value) : data(new int[n]), size(n) {
        for (int i = 0; i < size; i++) data[i] = value;
        cout << "[Parameterized constructor] size = " << size << "\n";
    }

    // RULE OF FIVE
    // If a class needs one of: destructor, copy constructor, copy assignment,
    // move constructor, move assignment, it almost always needs all five.

    // (1) DESTRUCTOR: releases the owned memory when the object is destroyed.
    ~IntArray() {
        cout << "[Destructor] freeing " << size << " ints\n";
        delete[] data;
    }

    // (2) COPY CONSTRUCTOR: builds a NEW object as a DEEP copy of another.
    // Each object gets its own separate memory, so there is no double delete.
    IntArray(const IntArray& other) : data(nullptr), size(other.size) {
        cout << "[Copy constructor]\n";
        if (size > 0) {
            data = new int[size];
            for (int i = 0; i < size; i++) data[i] = other.data[i];
        }
    }

    // (3) COPY ASSIGNMENT: overwrites an EXISTING object with a deep copy.
    IntArray& operator=(const IntArray& other) {
        cout << "[Copy assignment]\n";
        if (this != &other) {            // guard against self-assignment (a = a)
            delete[] data;               // free the old memory first
            size = other.size;
            data = (size > 0) ? new int[size] : nullptr;
            for (int i = 0; i < size; i++) data[i] = other.data[i];
        }
        return *this;
    }

    // (4) MOVE CONSTRUCTOR: STEALS the memory from a temporary object.
    // No copying, so it is fast. The source is left empty but valid.
    IntArray(IntArray&& other) noexcept : data(other.data), size(other.size) {
        cout << "[Move constructor]\n";
        other.data = nullptr;
        other.size = 0;
    }

    // (5) MOVE ASSIGNMENT: frees our memory, then steals from the source.
    IntArray& operator=(IntArray&& other) noexcept {
        cout << "[Move assignment]\n";
        if (this != &other) {
            delete[] data;               // release what we own
            data = other.data;           // take ownership
            size = other.size;
            other.data = nullptr;        // leave the source empty
            other.size = 0;
        }
        return *this;
    }

    // Helper to show the contents
    void print(const char* label) const {
        cout << label << " (size " << size << "): ";
        for (int i = 0; i < size; i++) cout << data[i] << " ";
        cout << "\n";
    }

    // Helper so we can show that a deep copy is independent
    void set(int index, int value) { if (index >= 0 && index < size) data[index] = value; }
};

// Returns a temporary object (used to trigger the move constructor)
IntArray makeArray() {
    return IntArray(3, 7);
}

int main() {
    cout << "--- 1. Default constructor ---\n";
    IntArray a;
    a.print("a");

    cout << "\n--- 2. Parameterized constructor ---\n";
    IntArray b(4, 5);
    b.print("b");

    cout << "\n--- 3. Copy constructor (deep copy) ---\n";
    IntArray c = b;          // c is a NEW object copied from b
    c.set(0, 99);            // change c only
    b.print("b");            // b must be unchanged
    c.print("c");

    cout << "\n--- 4. Copy assignment ---\n";
    a = b;                   // a already exists, so this is assignment
    a.print("a");

    cout << "\n--- 5. Move constructor ---\n";
    IntArray d = move(c);    // c's memory is stolen by d
    d.print("d");
    c.print("c (after move)");

    cout << "\n--- 6. Move assignment ---\n";
    IntArray e;
    e = makeArray();         // temporary is moved into e
    e.print("e");

    cout << "\n--- End of main: destructors run ---\n";
    return 0;
}