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
way for other code to use the object, and they check values first.