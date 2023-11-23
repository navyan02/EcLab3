#include <iostream>
#include <iomanip>

using namespace std;

class Account
{
protected:
    string accountNumber;
    string accountHolder;
    double balance;

public:
    Account(const string &number, const string &holder, double initialBalance)
        : accountNumber(number), accountHolder(holder), balance(initialBalance) {}

    string getAccountNumber() const
    {
        return accountNumber;
    }

    string getAccountHolder() const
    {
        return accountHolder;
    }

    virtual void displayDetails() const
    {
        cout << "   Holder: " << accountHolder << "\n";
        cout << "   Balance: $" << fixed << setprecision(2) << getBalance() << "\n";
    }

    double getBalance() const
    {
        return balance;
    }
    // Modify the deposit function in the Account class
    void deposit(double amount, bool showOutput = true)
    {
        if (amount > 0)
        {
            balance += amount;
        }
        else
        {
            cout << "Invalid deposit amount.\n";
        }
    }

    virtual void withdraw(double amount)
    {
        if (amount > 0 && getBalance() >= amount)
        {
            balance -= amount;
        }
        else
        {
            cout << "Invalid withdrawal amount or insufficient balance.\n";
        }
    }
};

class SavingsAccount : public Account
{
private:
    double interestRate;

public:
    SavingsAccount(const string &number, const string &holder, double initialBalance, double rate)
        : Account(number, holder, initialBalance), interestRate(rate) {}

    void displayDetails() const override
    {
        Account::displayDetails();
        cout << "   Interest Rate: " << fixed << setprecision(2) << (interestRate * 100) << "%\n";
    }

    void withdraw(double amount) override
    {
        double minimumBalance = 100.0; // Adjust as needed
        if (amount > 0 && (getBalance() - amount) >= minimumBalance)
        {
            balance -= amount;
        }
        else
        {
            cout << "Invalid withdrawal amount or would go below minimum balance.\n";
        }
    }
};

class CurrentAccount : public Account
{
private:
    double overdraftLimit;

public:
    CurrentAccount(const string &number, const string &holder, double initialBalance, double overdraft)
        : Account(number, holder, initialBalance), overdraftLimit(overdraft) {}

    void displayDetails() const override
    {
        Account::displayDetails();
        cout << "   Overdraft Limit: $" << fixed << setprecision(2) << overdraftLimit << "\n";
    }

    void withdraw(double amount) override
    {
        if (amount > 0 && (getBalance() - amount) >= -overdraftLimit)
        {
            balance -= amount;
        }
        else
        {
            cout << "Invalid withdrawal amount or would exceed overdraft limit.\n";
        }
    }
};

// Function to transfer money between accounts
void transferMoney(Account &from, Account &to, double amount)
{
    from.withdraw(amount);
    to.deposit(amount);
}

int main()
{
    SavingsAccount savings("S123", "John Doe", 1000.0, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000.0, 500.0);

    cout << "Account Details for Savings Account (ID: " << savings.getAccountNumber() << "):\n";
    savings.displayDetails();
    cout << "\n";

    cout << "Account Details for Current Account (ID: " << current.getAccountNumber() << "):\n";
    current.displayDetails();
    cout << "\n";

    // Use false as the second argument to suppress the output
    savings.deposit(500.0, false);
    current.withdraw(1000.0);

    cout << "Account Details after deposit and withdrawal:\n";
    cout << "Account Details for Savings Account (ID: " << savings.getAccountNumber() << "):\n";
    savings.displayDetails();
    cout << "\n";

    cout << "Account Details for Current Account (ID: " << current.getAccountNumber() << "):\n";
    current.displayDetails();
    cout << "\n";

    // Transfer money from savings to current
    transferMoney(savings, current, 300.0);

    cout << "Account Details after transfer:\n";
    cout << "Account Details for Savings Account (ID: " << savings.getAccountNumber() << "):\n";
    savings.displayDetails();
    cout << "\n";

    cout << "Account Details for Current Account (ID: " << current.getAccountNumber() << "):\n";
    current.displayDetails();
    cout << "\n";

    return 0;
}
