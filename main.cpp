/*
    Assignment: Extra Credit Lab 3
    Course: EECS 348
    Author: Jack Bauer
    Creation date: 11/25/2023
    Purpose: Simulat a banking application.
*/
#include <iostream> // For input / output
#include <string> // For ease of programming with strings
#include <iomanip> // For decimal precision

using namespace std;

// Super class - account
class Account {
    public:
        float balance;
        string accountNumber;
        string accountHolder;

        Account(string _accountNumber="N000", string _accountHolder="Unidentified", float _balance=0) {
            balance = _balance;
            accountNumber = _accountNumber;
            accountHolder = _accountHolder;
        }

        // Overload the assignment operator
        void operator= (const Account &obj) {
            balance = obj.balance;
        }

        // Overload the + operator
        Account operator+ (Account &obj) {
            int objBalInitial = obj.balance;
            obj.withdraw(300.00f);
            if (obj.balance == (objBalInitial - 300.00f)) {
                balance += 300.00f;
            }
            else {
                cout << "Unable to transfer balance." << endl;
            }
            return *this; // return the current account
        }

        void displayDetails() {
            cout << "Account Details for Savings Account (ID: " << accountNumber << "):" << endl;
            cout << "    Holder: " << accountHolder << endl;
            cout << "    Balance: $" << balance << "\n" << endl;
        }

        void deposit(float amount) {
            balance += amount;
        }

        void withdraw(float amount) {
            if (balance < amount || balance <= 0) {
                cout << "Insufficient funds." << endl;
                return;
            }
            balance -= amount;
        }
};

// Subclass derived as public Account
class SavingssAccount: public Account {
    private:
        float minimumBalance; // While not necessarily specified, is a better solution to hardcoding in a $500 overdraft limit

    public:
        float interestRate;

        SavingssAccount(string _accountNumber, string _accountHolder, float _balance, float _interestRate, float _minimumBalance=500.00f) {
            balance = _balance;
            interestRate = _interestRate * 100; // Input as a decimal value, multiply by 100 to get the percent value
            accountNumber = _accountNumber;
            accountHolder = _accountHolder;
            minimumBalance = _minimumBalance;
        }

        // Overload the + operator
        SavingssAccount operator+ (Account &obj) {
            int objBalInitial = obj.balance;
            obj.withdraw(300.00f);
            if (obj.balance == (objBalInitial - 300.00f)) {
                balance += 300.00f;
            }
            else {
                cout << "Unable to transfer balance." << endl;
            }
            return *this; // return the current account
        }

        // Override Account in order to implement interest rates
        void displayDetails() {
            cout << "Account Details for Savings Account (ID: " << accountNumber << "):" << endl;
            cout << "    Holder: " << accountHolder << endl;
            cout << "    Balance: $" << balance << endl;
            cout << "    Interest Rate: " << interestRate << "%"  << "\n" << endl;
        }

        // Override Account in order to implement a minimum balance
        void withdraw(float amount) {
            // Ensure proper validation for withdrawal operations on SavingsAccount
            if ((balance - amount) < minimumBalance) {
                cout << "Cannot withdraw below the minimum balance." << endl;
                return;
            }
            if (balance < amount || balance <= 0) {
                cout << "Insufficient funds." << endl;
                return;
            }
            balance -= amount;
        }
};

// Subclass derived as public Account
class CurrentAccount: public Account {
    public:
        float overdraftlimit;

        CurrentAccount(string _accountNumber, string _accountHolder, float _balance, float _overdraftlimit) {
            balance = _balance;
            overdraftlimit = _overdraftlimit;
            accountNumber = _accountNumber;
            accountHolder = _accountHolder;
        }

        // Overload the + operator
        CurrentAccount operator+ (Account &obj) {
            int objBalInitial = obj.balance;
            obj.withdraw(300.00f);
            if (obj.balance == (objBalInitial - 300.00f)) {
                balance += 300.00f;
            }
            else {
                cout << "Unable to transfer balance." << endl;
            }
            return *this; // return the current account
        }

        // Override Account in order to implement overdraft limits
        void displayDetails() {
            cout << "Account Details for Current Account (ID: " << accountNumber << "):" << endl;
            cout << "    Holder: " << accountHolder << endl;
            cout << "    Balance: $" << balance << endl;
            cout << "    Overdraft Limit: $" << overdraftlimit << "\n"  << endl;
        }

        // Override Account in order to implement overdraft limits
        void withdraw(float amount) {
            // Ensure proper validation for withdrawal operations on CurrentAccount
            if (amount > (balance + overdraftlimit)) {
                cout << "Cannot withdraw beyond the  overdraft limit" << endl;
                return;
            }
            balance -= amount;
        }
};

// Overload the << operator for generic Account
ostream &operator<< (ostream &output, const Account& acct) {
    output 
        << "Account Details for Account (ID: " << acct.accountNumber << "):" << endl
        << "    Holder: " << acct.accountHolder << endl
        << "    Balance: $" << acct.balance  << "\n" << endl;
    return output;
}

// Overload the << operator for savings Account
ostream &operator<< (ostream &output, const SavingssAccount& acct) {
    output 
        << "Account Details for Savings Account (ID: " << acct.accountNumber << "):" << endl
        << "    Holder: " << acct.accountHolder << endl
        << "    Balance: $" << acct.balance << endl
        << "    Interest Rate: " << acct.interestRate << "%"  << "\n" << endl;
    return output;
}

// Overload the << operator for current Account
ostream &operator<< (ostream &output, const CurrentAccount& acct) {
    output 
        << "Account Details for Current Account (ID: " << acct.accountNumber << "):" << endl
        << "    Holder: " << acct.accountHolder << endl
        << "    Balance: $" << acct.balance << endl
        << "    Overdraft Limit: $" << acct.overdraftlimit  << "\n" << endl;
    return output;
}

int main() {
    cout << setprecision(2) << fixed; // Set the precision of our decimal values to two places
    
    // Create instances of SavingsAccount and CurrentAccount
    SavingssAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    // Demonstrate balance inquiry for both account types
    savings.displayDetails();
    current.displayDetails();

    // Demonstrate deposit and withdrawal for both account types
    savings.deposit(1000);
    current.deposit(1000);
    savings.withdraw(500);
    current.withdraw(2000);

    // Display the details of all accounts after transaction
    cout << "Account Details after deposit and withdrawl:" << endl;
    cout << savings;
    cout << current;
    
    // Transfer 300 from savings to current using operator overloading
    current = current + savings;

    // Display the details of all accounts after transaction
    cout << "Account Details after transfer:" << endl;
    cout << savings;
    cout << current;

    return 0;
}