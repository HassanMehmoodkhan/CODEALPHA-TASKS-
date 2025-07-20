#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Transaction {
public:
    string type;
    double amount;
    string toAccount;

    Transaction(string t, double a, string to = "") : type(t), amount(a), toAccount(to) {}

    void display() {
        if (type == "Transfer")
            cout << type << " of $" << amount << " to " << toAccount << endl;
        else
            cout << type << " of $" << amount << endl;
    }
};

class Account {
private:
    string accNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(string number) : accNumber(number), balance(0.0) {}

    void deposit(double amount) {
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount));
        cout << "Deposited $" << amount << endl;
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
            return;
        }
        balance -= amount;
        transactions.push_back(Transaction("Withdraw", amount));
        cout << "Withdrew $" << amount << endl;
    }

    void transfer(Account &receiver, double amount) {
        if (amount > balance) {
            cout << "Transfer failed: Insufficient funds!" << endl;
            return;
        }
        balance -= amount;
        receiver.balance += amount;
        transactions.push_back(Transaction("Transfer", amount, receiver.accNumber));
        receiver.transactions.push_back(Transaction("Received", amount, accNumber));
        cout << "Transferred $" << amount << " to " << receiver.accNumber << endl;
    }

    void viewTransactions() {
        cout << "Transaction history for account " << accNumber << ":\n";
        for (auto &t : transactions)
            t.display();
    }

    void showBalance() {
        cout << "Balance for account " << accNumber << ": $" << balance << endl;
    }

    string getAccNumber() {
        return accNumber;
    }
};

class Customer {
public:
    string name;
    Account account;

    Customer(string n, string accNo) : name(n), account(accNo) {}
};

int main() {
    Customer customer1("Ali", "A1001");
    Customer customer2("Sara", "A1002");

    int choice;
    double amount;

    do {
        cout << "\n--- Banking Menu ---\n";
        cout << "1. Deposit\n2. Withdraw\n3. Transfer\n4. View Transactions\n5. Show Balance\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter amount to deposit: ";
                cin >> amount;
                customer1.account.deposit(amount);
                break;
            case 2:
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                customer1.account.withdraw(amount);
                break;
            case 3:
                cout << "Enter amount to transfer to Sara: ";
                cin >> amount;
                customer1.account.transfer(customer2.account, amount);
                break;
            case 4:
                customer1.account.viewTransactions();
                break;
            case 5:
                customer1.account.showBalance();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}