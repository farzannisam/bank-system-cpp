#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

class BankAccount
{
private:
    int accountNumber;
    char name[50];
    int age;
    char gender[10];
    char phone[15];
    char address[100];
    char accountType[20];
    float balance;
    int pin;

public:

    void createAccount()
    {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;

        cin.ignore();

        cout << "Enter Customer Name: ";
        cin.getline(name, 50);

        cout << "Enter Age: ";
        cin >> age;

        cin.ignore();

        cout << "Enter Gender: ";
        cin.getline(gender, 10);

        cout << "Enter Phone Number: ";
        cin.getline(phone, 15);

        cout << "Enter Address: ";
        cin.getline(address, 100);

        cout << "Enter Account Type (Savings/Current): ";
        cin.getline(accountType, 20);

        cout << "Enter Initial Deposit Amount: ";
        cin >> balance;

        cout << "Set 4-Digit PIN: ";
        cin >> pin;

        cout << "\nAccount Created Successfully!\n";
    }

    void displayAccount()
    {
        cout << "\n====================================";
        cout << "\nAccount Number : " << accountNumber;
        cout << "\nCustomer Name  : " << name;
        cout << "\nAge            : " << age;
        cout << "\nGender         : " << gender;
        cout << "\nPhone Number   : " << phone;
        cout << "\nAddress        : " << address;
        cout << "\nAccount Type   : " << accountType;
        cout << "\nBalance        : " << balance;
        cout << "\n====================================\n";
    }

    int getAccountNumber()
    {
        return accountNumber;
    }

    int getPin()
    {
        return pin;
    }

    void deposit()
    {
        float amount;

        cout << "\nEnter Amount to Deposit: ";
        cin >> amount;

        balance += amount;

        cout << "Deposit Successful!";
        cout << "\nUpdated Balance: " << balance << endl;
    }

    void withdraw()
    {
        float amount;

        cout << "\nEnter Amount to Withdraw: ";
        cin >> amount;

        if(amount > balance)
        {
            cout << "\nInsufficient Balance!\n";
        }
        else
        {
            balance -= amount;

            cout << "\nWithdrawal Successful!";
            cout << "\nRemaining Balance: " << balance << endl;
        }
    }

    void balanceInquiry()
    {
        cout << "\nCurrent Balance: " << balance << endl;
    }

    void updateDetails()
    {
        cin.ignore();

        cout << "\nEnter New Phone Number: ";
        cin.getline(phone, 15);

        cout << "Enter New Address: ";
        cin.getline(address, 100);

        cout << "\nDetails Updated Successfully!\n";
    }
};

void writeAccount()
{
    BankAccount acc;

    ofstream outFile;

    outFile.open("bank.dat", ios::binary | ios::app);

    acc.createAccount();

    outFile.write(reinterpret_cast<char*>(&acc), sizeof(acc));

    outFile.close();
}

void displayAllAccounts()
{
    BankAccount acc;

    ifstream inFile;

    inFile.open("bank.dat", ios::binary);

    if(!inFile)
    {
        cout << "\nFile Not Found!\n";
        return;
    }

    while(inFile.read(reinterpret_cast<char*>(&acc), sizeof(acc)))
    {
        acc.displayAccount();
    }

    inFile.close();
}

void searchAccount()
{
    BankAccount acc;

    int accNo;
    bool found = false;

    cout << "\nEnter Account Number to Search: ";
    cin >> accNo;

    ifstream inFile("bank.dat", ios::binary);

    while(inFile.read(reinterpret_cast<char*>(&acc), sizeof(acc)))
    {
        if(acc.getAccountNumber() == accNo)
        {
            acc.displayAccount();
            found = true;
            break;
        }
    }

    inFile.close();

    if(!found)
    {
        cout << "\nAccount Not Found!\n";
    }
}

void depositMoney()
{
    BankAccount acc;

    int accNo;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    while(file.read(reinterpret_cast<char*>(&acc), sizeof(acc)))
    {
        if(acc.getAccountNumber() == accNo)
        {
            acc.deposit();

            int pos = (-1) * static_cast<int>(sizeof(acc));

            file.seekp(pos, ios::cur);

            file.write(reinterpret_cast<char*>(&acc), sizeof(acc));

            found = true;
            break;
        }
    }

    file.close();

    if(!found)
    {
        cout << "\nAccount Not Found!\n";
    }
}

void withdrawMoney()
{
    BankAccount acc;

    int accNo;
    int enteredPin;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    cout << "Enter PIN: ";
    cin >> enteredPin;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    while(file.read(reinterpret_cast<char*>(&acc), sizeof(acc)))
    {
        if(acc.getAccountNumber() == accNo &&
           acc.getPin() == enteredPin)
        {
            acc.withdraw();

            int pos = (-1) * static_cast<int>(sizeof(acc));

            file.seekp(pos, ios::cur);

            file.write(reinterpret_cast<char*>(&acc), sizeof(acc));

            found = true;
            break;
        }
    }

    file.close();

    if(!found)
    {
        cout << "\nInvalid Account Number or PIN!\n";
    }
}

void balanceInquiry()
{
    BankAccount acc;

    int accNo;
    int enteredPin;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    cout << "Enter PIN: ";
    cin >> enteredPin;

    ifstream inFile("bank.dat", ios::binary);

    while(inFile.read(reinterpret_cast<char*>(&acc), sizeof(acc)))
    {
        if(acc.getAccountNumber() == accNo &&
           acc.getPin() == enteredPin)
        {
            acc.balanceInquiry();
            found = true;
            break;
        }
    }

    inFile.close();

    if(!found)
    {
        cout << "\nInvalid Account Number or PIN!\n";
    }
}

void updateAccount()
{
    BankAccount acc;

    int accNo;
    bool found = false;

    cout << "\nEnter Account Number to Update: ";
    cin >> accNo;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    while(file.read(reinterpret_cast<char*>(&acc), sizeof(acc)))
    {
        if(acc.getAccountNumber() == accNo)
        {
            acc.updateDetails();

            int pos = (-1) * static_cast<int>(sizeof(acc));

            file.seekp(pos, ios::cur);

            file.write(reinterpret_cast<char*>(&acc), sizeof(acc));

            found = true;

            break;
        }
    }

    file.close();

    if(!found)
    {
        cout << "\nAccount Not Found!\n";
    }
}

void deleteAccount()
{
    BankAccount acc;

    int accNo;
    bool found = false;

    cout << "\nEnter Account Number to Delete: ";
    cin >> accNo;

    ifstream inFile("bank.dat", ios::binary);

    ofstream outFile("temp.dat", ios::binary);

    while(inFile.read(reinterpret_cast<char*>(&acc), sizeof(acc)))
    {
        if(acc.getAccountNumber() == accNo)
        {
            found = true;
        }
        else
        {
            outFile.write(reinterpret_cast<char*>(&acc), sizeof(acc));
        }
    }

    inFile.close();
    outFile.close();

    remove("bank.dat");
    rename("temp.dat", "bank.dat");

    if(found)
    {
        cout << "\nAccount Deleted Successfully!\n";
    }
    else
    {
        cout << "\nAccount Not Found!\n";
    }
}

int main()
{
    int choice;

    do
    {
        cout << "\n========================================";
        cout << "\n      BANK MANAGEMENT SYSTEM";
        cout << "\n========================================";

        cout << "\n1. Create Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Balance Inquiry";
        cout << "\n5. Display All Accounts";
        cout << "\n6. Search Account";
        cout << "\n7. Update Account";
        cout << "\n8. Delete Account";
        cout << "\n9. Exit";

        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                writeAccount();
                break;

            case 2:
                depositMoney();
                break;

            case 3:
                withdrawMoney();
                break;

            case 4:
                balanceInquiry();
                break;

            case 5:
                displayAllAccounts();
                break;

            case 6:
                searchAccount();
                break;

            case 7:
                updateAccount();
                break;

            case 8:
                deleteAccount();
                break;

            case 9:
                cout << "\nThank You for Using the System!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 9);

    return 0;
}