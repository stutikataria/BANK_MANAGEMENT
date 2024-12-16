#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;
class BankAccount{
private:
    string name;
    int accountNum;
    double balance;
public:
    // Constructor
    BankAccount(string n, int ac, double bal) {
        name = n;
        accountNum = ac;
        balance = bal;
    }
    BankAccount() {} // Default constructor for file handling

    string getName() {
        return name;
    }

    int getAccountNum() {
        return accountNum;
    }

    double getBalance() {
        return balance;
    }

    void setName(string n) {
        name = n;
    }

    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "\t\tWithdraw Successfully...." << endl;
        } else {
            cout << "\t\tInsufficient Balance...." << endl;
        }
    }

    friend ostream& operator<<(ostream& os, const BankAccount& account) {
        os << account.name << " " << account.accountNum << " " << account.balance;
        return os;
    }

    friend istream& operator>>(istream& is, BankAccount& account) {
        is >> account.name >> account.accountNum >> account.balance;
        return is;
    }
};

class BankManagement {
private:
    vector<BankAccount> accounts;
    const string filename = "accounts.txt";

    void saveToFile() {
    ofstream file(filename);  // Opening the file for output
    for (const auto& account : accounts) {
        file << account << endl;  // Saving account data to file
    }
    file.close();  // Closing the file
}


    void loadFromFile() {
        ifstream file(filename, ios::in);
        if (file.is_open()) {
            BankAccount account;
            while (file >> account) {
                accounts.push_back(account);
            }
            file.close();
        }
    }

public:
    BankManagement() {
        loadFromFile();
    }

    ~BankManagement() {
        saveToFile();
    }

    void AddAccount(string name, int accountNum, double balance) {
        accounts.push_back(BankAccount(name, accountNum, balance));
    }

    void ShowAllAccounts() {
        cout << "\t\tAll Account Holders" << endl;
        for (int i = 0; i < accounts.size(); i++) {
            cout << "Name: " << accounts[i].getName() << endl
                 << "Account Number: " << accounts[i].getAccountNum() << endl
                 << "Balance: " << accounts[i].getBalance() << endl;
        }
    }

    void searchAccount(int account) {
        cout << "\t\tAccount Holder " << endl;
        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].getAccountNum() == account) {
                cout << "Name: " << accounts[i].getName() << endl
                     << "Account Number: " << accounts[i].getAccountNum() << endl
                     << "Balance: " << accounts[i].getBalance() << endl;
                return;
            }
        }
        cout << "\t\tAccount Not Found...." << endl;
    }

    BankAccount* findAccount(int accountNum) {
        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].getAccountNum() == accountNum) {
                return &accounts[i];
            }
        }
        return NULL;
    }

    void updateAccountDetails(int accountNum) {
        BankAccount* account = findAccount(accountNum);
        if (account != NULL) {
            string newName;
            cout << "\t\tEnter new name for the account: ";
            cin >> newName;
            account->setName(newName);
            cout << "\t\tAccount details updated successfully...." << endl;
        } else {
            cout << "\t\tAccount Not Found...." << endl;
        }
    }

    void deleteAccount(int accountNum) {
        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].getAccountNum() == accountNum) {
                accounts.erase(accounts.begin() + i);
                cout << "\t\tAccount deleted successfully...." << endl;
                return;
            }
        }
        cout << "\t\tAccount Not Found...." << endl;
    }
};

int main() {
    BankManagement bank;
    int choice;
    char op;
    do {
        system("cls");
        cout << "\t\t::Bank Management System" << endl;
        cout << "\t\t\t Main Menu" << endl;
        cout << "\t\t1. Create Account" << endl;
        cout << "\t\t2. Show All Accounts" << endl;
        cout << "\t\t3. Search Account" << endl;
        cout << "\t\t4. Deposit Money" << endl;
        cout << "\t\t5. Withdraw Money" << endl;
        cout << "\t\t6. Update Customer Details" << endl;
        cout << "\t\t7. Delete Account" << endl;
        cout << "\t\t8. Exit" << endl;
        cout << "\t\t----------------------" << endl;
        cout << "\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            int accountNum;
            double balance;
            cout << "\t\tEnter Name: ";
            cin >> name;
            cout << "\t\tEnter Account Number: ";
            cin >> accountNum;
            cout << "\t\tEnter Balance: ";
            cin >> balance;
            bank.AddAccount(name, accountNum, balance);
            cout << "\t\tAccount Created Successfully..." << endl;
            break;
        }
        case 2: {
            bank.ShowAllAccounts();
            break;
        }
        case 3: {
            int accountNum;
            cout << "Enter Account Number: ";
            cin >> accountNum;
            bank.searchAccount(accountNum);
            break;
        }
        case 4: {
            int accountNum;
            double amount;
            cout << "\t\tEnter Account Number to Deposit Money: ";
            cin >> accountNum;
            BankAccount* account = bank.findAccount(accountNum);
            if (account != NULL) {
                cout << "\t\tEnter Amount to Deposit: ";
                cin >> amount;
                account->deposit(amount);
                cout << "\t\t" << amount << " Deposited Successfully...." << endl;
            } else {
                cout << "\t\tAccount Not Found...." << endl;
            }
            break;
        }
        case 5: {
            int accountNum;
            double amount;
            cout << "\t\tEnter Account Number to Withdraw Money: ";
            cin >> accountNum;
            BankAccount* account = bank.findAccount(accountNum);
            if (account != NULL) {
                cout << "\t\tEnter Amount to Withdraw: ";
                cin >> amount;
                account->withdraw(amount);
            } else {
                cout << "\t\tAccount Not Found...." << endl;
            }
            break;
        }
        case 6: {
            int accountNum;
            cout << "\t\tEnter Account Number to Update Details: ";
            cin >> accountNum;
            bank.updateAccountDetails(accountNum);
            break;
        }
        case 7: {
            int accountNum;
            cout << "\t\tEnter Account Number to Delete: ";
            cin >> accountNum;
            bank.deleteAccount(accountNum);
            break;
        }
        case 8: {
            exit(1);
            break;
        }
        default: {
            cout << "\t\tInvalid Choice!" << endl;
            break;
        }
        }
        cout << "\t\tDo you want to continue or Exit [Yes/No]? ";
        cin >> op;
    } while (op == 'y' || op == 'Y');

    return 0;
}

