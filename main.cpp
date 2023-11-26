#include <iostream>
#include <string>
#include <cmath>

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
        Account operator+ (Account const &obj) {
            balance += obj.balance;
            return *this; // return the current account
        }

        void displayDetails() {
            cout << "Account Details for Savings Account (ID: " << accountNumber << "):" << endl;
            cout << "    Holder: " << accountHolder << endl;
            cout << "    Balance: $" << balance << endl;
        }

        void deposit(float amount) {
            balance += amount;
        }

        void withdraw(float amount) {
            if (balance < amount || balance <= 0) {
                cout << "Insufficient funds.";
                return;
            }
            balance -= amount;
        }
};

// Subclass derived as public Account
class SavingssAccount: public Account {
    private:
        float minimumBalance;

    public:
        float interestRate;

        SavingssAccount(string _accountNumber, string _accountHolder, float _balance, float _interestRate, float _minimumBalance=500.00f) {
            balance = _balance;
            interestRate = _interestRate;
            accountNumber = _accountNumber;
            accountHolder = _accountHolder;
            minimumBalance = _minimumBalance;
        }

        void displayDetails() {
            cout << "Account Details for Savings Account (ID: " << accountNumber << "):" << endl;
            cout << "    Holder: " << accountHolder << endl;
            cout << "    Balance: $" << balance << endl;
            cout << "    Interest Rate: " << interestRate << "%" << endl;
        }

        void withdraw(float amount) {
            if ((balance - amount) < minimumBalance) {
                cout << "Cannot withdraw below the minimum balance.";
                return;
            }
            if (balance < amount || balance <= 0) {
                cout << "Insufficient funds.";
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

        void displayDetails() {
            cout << "Account Details for Current Account (ID: " << accountNumber << "):" << endl;
            cout << "    Holder: " << accountHolder << endl;
            cout << "    Balance: $" << balance << endl;
            cout << "    Overdraft Limit: $" << overdraftlimit << endl;
        }

        void withdraw(float amount) {
            if (amount > (balance + overdraftlimit)) {
                cout << "Cannot withdraw beyond the  overdraft limit";
                return;
            }
            balance -= amount;
        }
};

// Overload the << operator
ostream &operator<< (ostream &output, const Account& acct) {
    output << acct.outDetails();
    return output;
}

int main() {
    SavingssAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    savings.displayDetails();
    current.displayDetails();

    savings.deposit(500);
    current.deposit(300);
    current.withdraw(1000);
    savings.withdraw(800);
    cout << "Account Details after deposit and withdrawl";

    savings.displayDetails();
    current.displayDetails();

    current = current + savings;
    cout << "Account Details after transfer:";

    savings.displayDetails();
    current.displayDetails();

    return 0;
}