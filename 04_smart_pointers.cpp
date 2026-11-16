// Practical 04: RAII and Smart Pointers
// RAII = Resource Acquisition Is Initialization.
// A resource (memory, file, lock...) is tied to an object's lifetime:
// it is acquired when the object is created and released automatically
// when the object is destroyed. No manual delete is needed.

#include <iostream>
#include <memory>    // unique_ptr, shared_ptr, make_unique, make_shared
#include <string>
#include <vector>
#include <chrono>
using namespace std;

// A small class that announces when it is created and destroyed,
// so we can SEE the lifetime of each object in the output.
class Resource {
private:
    string name;
public:
    Resource(const string& n) : name(n) {
        cout << "  [Created]   " << name << "\n";
    }
    ~Resource() {
        cout << "  [Destroyed] " << name << "\n";
    }
    void use() const {
        cout << "  Using " << name << "\n";
    }
    string getName() const { return name; }
};

// ---------------------------------------------------------------
// PART 1: Raw pointer (the OLD way) - shown only for comparison
// ---------------------------------------------------------------
void rawPointerDemo() {
    cout << "\n=== Part 1: Raw pointer (manual new/delete) ===\n";
    Resource* r = new Resource("RawResource");
    r->use();
    delete r;   // we MUST remember this. If we forget, or an exception is
                // thrown before this line, the memory leaks.
}

// ---------------------------------------------------------------
// PART 2: unique_ptr - exactly ONE owner
// ---------------------------------------------------------------
void uniquePtrDemo() {
    cout << "\n=== Part 2: unique_ptr (single owner) ===\n";
    unique_ptr<Resource> p1 = make_unique<Resource>("UniqueResource");
    p1->use();

    // A unique_ptr CANNOT be copied (that would mean two owners):
    // unique_ptr<Resource> p2 = p1;   // ERROR: copy is deleted

    // Ownership can only be MOVED. p1 becomes empty, p2 owns the object.
    unique_ptr<Resource> p2 = move(p1);
    cout << "  After move: p1 is " << (p1 ? "not empty" : "empty (nullptr)") << "\n";
    cout << "  After move: p2 is " << (p2 ? "not empty" : "empty (nullptr)") << "\n";
    p2->use();

    // unique_ptr also works for arrays
    unique_ptr<int[]> arr = make_unique<int[]>(5);
    for (int i = 0; i < 5; i++) arr[i] = (i + 1) * 10;
    cout << "  Array: ";
    for (int i = 0; i < 5; i++) cout << arr[i] << " ";
    cout << "\n";

    cout << "  Leaving function: p2 and arr are destroyed automatically.\n";
}   // no delete needed

// ---------------------------------------------------------------
// PART 3: shared_ptr - SHARED ownership with a reference count
// ---------------------------------------------------------------

// Two "parts of the program" that both genuinely need the same object.
class Printer {
    shared_ptr<Resource> doc;
public:
    Printer(shared_ptr<Resource> d) : doc(d) {}
    void print() const { cout << "  Printer prints: " << doc->getName() << "\n"; }
};

class Scanner {
    shared_ptr<Resource> doc;
public:
    Scanner(shared_ptr<Resource> d) : doc(d) {}
    void scan() const { cout << "  Scanner scans : " << doc->getName() << "\n"; }
};

void sharedPtrDemo() {
    cout << "\n=== Part 3: shared_ptr (shared ownership) ===\n";
    shared_ptr<Resource> doc = make_shared<Resource>("SharedDocument");
    cout << "  Owners (use_count) after creation: " << doc.use_count() << "\n";

    {
        Printer printer(doc);
        Scanner scanner(doc);
        cout << "  Owners after Printer and Scanner join: " << doc.use_count() << "\n";
        printer.print();
        scanner.scan();
        cout << "  Leaving inner block: Printer and Scanner are destroyed.\n";
    }

    cout << "  Owners after inner block: " << doc.use_count() << "\n";
    cout << "  The object is still alive because 'doc' still owns it.\n";
}   // last owner goes away here, so the Resource is destroyed now

// ---------------------------------------------------------------
// PART 4: Many iterations - no leaks with smart pointers
// ---------------------------------------------------------------
void manyIterations() {
    cout << "\n=== Part 4: 100000 iterations with unique_ptr ===\n";
    long long sum = 0;
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < 100000; i++) {
        unique_ptr<int[]> buf = make_unique<int[]>(100);
        buf[0] = i;
        sum += buf[0];
    }   // each buffer is freed automatically at the end of every loop pass
    auto end = chrono::steady_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "  Sum = " << sum << "\n";
    cout << "  Time taken = " << ms << " ms (depends on this computer)\n";
}

int main() {
    rawPointerDemo();
    uniquePtrDemo();
    sharedPtrDemo();
    manyIterations();
    cout << "\nProgram finished.\n";
    return 0;
}