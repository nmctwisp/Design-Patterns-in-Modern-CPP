#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Memento {
	int balance;
public:
	Memento(int balance) : balance(balance) {};
	friend class BankAccount;
};

class BankAccount {
	int balance{ 0 };
public:
	BankAccount(int balance) : balance(balance) {}

	Memento deposit(int amt) { 
		balance += amt; 

		return Memento(balance);
	};

	void restore(const Memento& m) {
		balance = m.balance;
	}

	friend std::ostream& operator<<(std::ostream& os, const BankAccount& account) {
		os << "balance: " << account.balance;
		return os;
	}

};

int main() {
	BankAccount ba{ 100 };
	auto m1 = ba.deposit(50);
	auto m2 = ba.deposit(25);

	std::cout << ba << std::endl;
	
	ba.restore(m1);
	std::cout << "back to m1: " << ba << std::endl;

	ba.restore(m2);
	std::cout << "back to m2: " << ba << std::endl;

	return 0;
}
