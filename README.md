# C++ Practicals

Practical work for the C++ Programming course (RSSOFTTECS Solutions).

## Practical 01: C++ Fundamentals
Demonstrates data types, constants, variables, operators and
input/output using a simple student result calculator.

**Compile:** `g++ 01_cpp_fundamentals.cpp -o fundamentals`

**Run:** `./fundamentals`

## Sample Output

~~~
Enter student name: shreya
Enter marks in 3 subjects (out of 100): 78 65 82

----- Result -----
Name    : shreya
Total   : 225 / 300
Average : 75
Grade   : A
Status  : PASS
Total % 7 = 1
~~~
## Practical 02: Classes, Access Specifiers and Member Functions
A BankAccount class with private data (account number, holder name,
balance) and public functions (deposit, withdraw, display).

**Compile:** `g++ 02_bank_account.cpp -o bank_account`

**Run:** `./bank_account`

**Private vs public:** Private members can only be used inside the class,
which protects the data from invalid changes. Public members are the safe
way for other code to use the object, and they check values first.## Practical 03: Constructors and Rule of Five
An IntArray class that owns a dynamic array and implements the default,
parameterized, copy and move constructors, copy and move assignment, and
the destructor.

**Compile:** `g++ -std=c++17 03_rule_of_five.cpp -o rule_of_five`

**Run:** `./rule_of_five`


## Practical 04: RAII and Smart Pointers
Compares raw pointers, unique_ptr (single owner) and shared_ptr (shared
ownership) using a Resource class that prints when it is created and
destroyed.

**Compile:** `g++ -std=c++17 04_smart_pointers.cpp -o smart_pointers`

**Run:** `./smart_pointers`

## Practical 05: Single and Multilevel Inheritance
University example: Person -> Student -> GraduateStudent. Shows single and
multilevel inheritance, constructor and destructor order, and which
inherited members each class can access.

**Compile:** `g++ -std=c++17 05_inheritance.cpp -o inheritance`

**Run:** `./inheritance`

## Practical 06: Runtime Polymorphism and Abstract Classes
An abstract Shape class with Circle, Rectangle and Triangle, each
implementing area(). Shape pointers call the correct area() at runtime.

**Compile:** `g++ -std=c++17 06_polymorphism.cpp -o polymorphism`

**Run:** `./polymorphism`

## Practical 07: Function and Operator Overloading
Overloaded add() functions for int, double, three ints and strings, and a
ComplexNumber class with overloaded +, -, == and << operators.

**Compile:** `g++ -std=c++17 07_overloading.cpp -o overloading`

**Run:** `./overloading`

## Practical 08: Factory Design Pattern
A VehicleFactory creates Car, Bike or Truck objects from a requested type
and returns them through a common Vehicle interface.

**Compile:** `g++ -std=c++17 08_factory_pattern.cpp -o factory`

**Run:** `./factory`
## Practical 09: Generic Stack Using Templates
A Stack<T> class template (backed by std::vector) tested with int, float
and std::string, including empty-stack error handling.

**Compile:** `g++ -std=c++17 09_template_stack.cpp -o template_stack`

**Run:** `./template_stack`
## Practical 10: Custom Exceptions
A BankAccount with a custom exception hierarchy (BankException,
InvalidAmount, InsufficientFunds) for deposits, withdrawals and transfers.

**Compile:** `g++ -std=c++17 10_custom_exceptions.cpp -o custom_exceptions`

**Run:** `./custom_exceptions`





