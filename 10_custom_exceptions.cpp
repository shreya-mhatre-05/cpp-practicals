// Practical 10: Custom Exceptions - Banking Transaction
// Exception hierarchy:
//
//   std::exception
//        |
//   BankException               (base for all banking errors)
//        |
//        +---- InvalidAmount
//        +---- InsufficientFunds

#include <iostream>
#include <exception>
#include <string>
using namespace std;

// ---------------- Custom exceptions ----------------

// Base class for every banking error
class BankException : public exception {
protected:
    string message;
public:
    BankException(const string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// Thrown when the amount is zero or negative
class InvalidAmount : public BankException {
public:
    InvalidAmount(double amount)
        : BankException("Invalid amount: " + to_string(amount) + " (must be greater than 0)") {}
};

// Thrown when the withdrawal is larger than the balance
class InsufficientFunds : public BankException {
public:
    InsufficientFunds(double balance, double requested)
        : BankException("Insufficient funds: balance is " + to_string(balance) +
                        " but " + to_string(requested) + " was requested") {}
};

// ---------------- BankAccount ----------------
class BankAccount {
private:
    string owner;
    double balance;
public:
    BankAccount(const string& o, double b) : owner(o), balance(b) {}

    double getBalance() const { return balance; }

    void deposit(double amount) {
        if (amount <= 0) throw InvalidAmount(amount);    // check FIRST
        balance += amount;                               // change only if valid
    }

    void withdraw(double amount) {
        if (amount <= 0) throw InvalidAmount(amount);
        if (amount > balance) throw InsufficientFunds(balance, amount);
        balance -= amount;                               // change only if valid
    }

    void transfer(BankAccount& to, double amount) {
        withdraw(amount);       // may throw; if it does, nothing below runs
        to.deposit(amount);
    }

    void show() const {
        cout << "  " << owner << "'s balance: " << balance << "\n";
    }
};

// Runs one withdrawal and reports the result
void tryWithdraw(BankAccount& acc, double amount) {
    cout << "\nWithdraw " << amount << ":\n";
    try {
        acc.withdraw(amount);
        cout << "  Success.\n";
    }
    catch (const InvalidAmount& e) {                // catch each type separately
        cout << "  InvalidAmount caught -> " << e.what() << "\n";
    }
    catch (const InsufficientFunds& e) {
        cout << "  InsufficientFunds caught -> " << e.what() << "\n";
    }
    acc.show();                                     // balance after the attempt
}

int main() {
    BankAccount shreya("Shreya", 5000);
    BankAccount rahul("Rahul", 1000);

    cout << "=== Starting balances ===\n";
    shreya.show();
    rahul.show();

    cout << "\n=== Withdrawals ===";
    tryWithdraw(shreya, 1500);     // success
    tryWithdraw(shreya, 10000);    // InsufficientFunds
    tryWithdraw(shreya, -200);     // InvalidAmount
    tryWithdraw(shreya, 0);        // InvalidAmount

    cout << "\n=== Transfers ===\n";
    try {
        shreya.transfer(rahul, 1000);
        cout << "  Transfer of 1000 succeeded.\n";
        shreya.transfer(rahul, 50000);
        cout << "  (this line is never reached)\n";
    }
    catch (const BankException& e) {                // base class catches any bank error
        cout << "  BankException caught -> " << e.what() << "\n";
    }
    shreya.show();
    rahul.show();

    return 0;
}
