#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <string>

using namespace std;

class BankCredit {
private:
    string name;
    double amount;
    string currency;
    double interestRate;

public:
    BankCredit() : amount(0), interestRate(0) {}

    BankCredit(const string& name, double amount, const string& currency, double interestRate)
        : name(name), amount(amount), currency(currency), interestRate(interestRate) {
    }

    BankCredit(const BankCredit& other)
        : name(other.name), amount(other.amount), currency(other.currency), interestRate(other.interestRate) {
    }

    BankCredit(BankCredit&& other) noexcept
        : name(move(other.name)), amount(other.amount), currency(move(other.currency)), interestRate(other.interestRate) {
    }

    BankCredit& operator=(const BankCredit& other) {
        if (this != &other) {
            name = other.name;
            amount = other.amount;
            currency = other.currency;
            interestRate = other.interestRate;
        }
        return *this;
    }

    BankCredit& operator=(BankCredit&& other) noexcept {
        if (this != &other) {
            name = move(other.name);
            amount = other.amount;
            currency = move(other.currency);
            interestRate = other.interestRate;
        }
        return *this;
    }

    string getName() const { return name; }
    double getAmount() const { return amount; }
    string getCurrency() const { return currency; }
    double getInterestRate() const { return interestRate; }

    friend ostream& operator<<(ostream& os, const BankCredit& credit) {
        os << "Name: " << credit.name << ", Amount: " << credit.amount << " " << credit.currency
            << ", Interest Rate: " << credit.interestRate << "%";
        return os;
    }

    bool operator<(const BankCredit& other) const {
        return amount < other.amount;
    }

    bool operator==(const BankCredit& other) const {
        return name == other.name && amount == other.amount &&
            currency == other.currency && interestRate == other.interestRate;
    }
};


struct BankCreditHash {
    size_t operator()(const BankCredit& credit) const {
        return hash<string>()(credit.getName()) ^
            hash<double>()(credit.getAmount()) ^
            hash<string>()(credit.getCurrency()) ^
            hash<double>()(credit.getInterestRate());
    }
};


template<typename Container>
void printContainer(const Container& container, ostream& os) {
    for (const auto& credit : container) {
        os << credit << endl;
    }
}

int main() {
    vector<BankCredit> credits;

 
    ifstream inputFile("input.txt");

    string name, currency;
    double amount, interestRate;
    while (inputFile >> name >> amount >> currency >> interestRate) {
        credits.emplace_back(name, amount, currency, interestRate);
    }
    inputFile.close();

    cout << "Original container:" << endl;
    printContainer(credits, cout);

    sort(credits.begin(), credits.end());
    cout << "\nSorted vector:" << endl;
    printContainer(credits, cout);

    set<BankCredit> creditSet(credits.begin(), credits.end());
    cout << "\nSet container:" << endl;
    printContainer(creditSet, cout);


    unordered_set<BankCredit, BankCreditHash> creditUnorderedSet(credits.begin(), credits.end());
    cout << "\nUnordered set container:" << endl;
    printContainer(creditUnorderedSet, cout);

    return 0;
}