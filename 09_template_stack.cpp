// Practical 09: Generic Stack using Templates
// One class template works for int, float, std::string and more.
// The compiler generates a separate class for each type that is used.

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
class Stack {
private:
    vector<T> items;      // the STL container that stores the data
public:
    // Add an item to the top
    void push(const T& value) {
        items.push_back(value);
    }

    // Remove the top item. Throws if the stack is empty.
    void pop() {
        if (items.empty()) {
            throw out_of_range("Cannot pop: the stack is empty");
        }
        items.pop_back();
    }

    // Safe way to look at the top item. Throws if the stack is empty.
    const T& top() const {
        if (items.empty()) {
            throw out_of_range("Cannot read top: the stack is empty");
        }
        return items.back();
    }

    bool empty() const { return items.empty(); }
    size_t size() const { return items.size(); }
};

// A helper template function that works with any Stack<T>
template <typename T>
void demo(const string& label, Stack<T>& s, T a, T b, T c) {
    cout << "--- " << label << " ---\n";
    s.push(a);
    s.push(b);
    s.push(c);
    cout << "  Pushed 3 items. Size = " << s.size() << "\n";
    cout << "  Top = " << s.top() << "\n";
    s.pop();
    cout << "  After one pop, top = " << s.top() << "\n";
    cout << "  Empty? " << (s.empty() ? "yes" : "no") << "\n";
}

int main() {
    // The same template is used three times with three different types.
    Stack<int> intStack;
    Stack<float> floatStack;
    Stack<string> stringStack;

    cout << "=== 1. Normal use with three data types ===\n";
    demo<int>("Stack<int>", intStack, 10, 20, 30);
    demo<float>("Stack<float>", floatStack, 1.5f, 2.5f, 3.5f);
    demo<string>("Stack<string>", stringStack, "apple", "banana", "cherry");

    cout << "\n=== 2. Empty-container test ===\n";
    Stack<int> emptyStack;
    cout << "  New stack empty? " << (emptyStack.empty() ? "yes" : "no") << "\n";
    try {
        emptyStack.pop();                       // invalid operation
    } catch (const out_of_range& e) {
        cout << "  Caught error: " << e.what() << "\n";
    }
    try {
        cout << emptyStack.top() << "\n";       // invalid operation
    } catch (const out_of_range& e) {
        cout << "  Caught error: " << e.what() << "\n";
    }

    cout << "\n=== 3. Emptying a stack completely ===\n";
    intStack.pop();
    intStack.pop();
    cout << "  intStack empty now? " << (intStack.empty() ? "yes" : "no") << "\n";

    return 0;
}
