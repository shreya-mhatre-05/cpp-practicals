// Practical 02: Classes, Access Specifiers and Member Functions
// A BankAccount class that keeps its data private and exposes
// safe public functions to work with it.

#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    // PRIVATE members: only code inside this class can touch them directly.
    // This protects the data - nobody outside can set balance to a wrong value.
    int accountNumber;
    string holderName;
    double balance;

public:
    // PUBLIC members: the safe "doorway" other code uses to work with the account.

    // Constructor: runs automatically when an object is created.
    // It validates the starting values.
    BankAccount(int accNo, string name, double initialBalance) {
        accountNumber = accNo;
        holderName = name;
        if (initialBalance >= 0) {
            balance = initialBalance;
        } else {
            cout << "Invalid opening balance. Setting balance to 0.\n";
            balance = 0;
        }
    }

    // Deposit money (amount must be positive)
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited " << amount << " successfully.\n";
        } else {
            cout << "Deposit amount must be greater than 0.\n";
        }
    }

    // Withdraw money (amount must be positive and not more than the balance)
    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Withdraw amount must be greater than 0.\n";
        } else if (amount > balance) {
            cout << "Insufficient balance. Withdrawal failed.\n";
        } else {
            balance -= amount;
            cout << "Withdrew " << amount << " successfully.\n";
        }
    }

    // Display the account details
    void display() const {
        cout << "Account No : " << accountNumber << endl;
        cout << "Holder     : " << holderName << endl;
        cout << "Balance    : " << balance << endl;
    }
};

int main() {
    // Object 1
    BankAccount acc1(101, "Shreya", 5000);
    cout << "--- Account 1 ---\n";
    acc1.display();
    acc1.deposit(2000);
    acc1.withdraw(1500);
    acc1.display();

    // Object 2
    BankAccount acc2(102, "Rahul", 1000);
    cout << "\n--- Account 2 ---\n";
    acc2.display();
    acc2.withdraw(3000);   // too much, should fail
    acc2.deposit(500);
    acc2.display();

    // acc1.balance = 999999;  // ERROR: 'balance' is private, cannot access it here

    return 0;
}