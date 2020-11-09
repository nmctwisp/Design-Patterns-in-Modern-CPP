#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Memento {
	int balance;
public:
	Memento(int balance) : balance(balance) {};
	Memento() : balance(0) {};
	friend class BankAccount;
};

class BankAccount {
	int balance{ 0 };
	std::vector<std::shared_ptr<Memento>> changes;
	int current;

public:

	BankAccount(int balance) :
		balance(balance),
		current(0) {
		
		changes.emplace_back(std::make_shared<Memento>(balance));
	};

	std::shared_ptr<Memento> deposit(int amt) {
		balance += amt;
		
		auto m = std::make_shared<Memento>(balance);
		changes.push_back(m);
		
		++current;

		return m;
	}

	void restore(const std::shared_ptr<Memento>& m) {
	
		if (m) {
			balance = m->balance;
			changes.push_back(m);
			current = changes.size() - 1;
		};
	}

	std::shared_ptr<Memento> undo() {

		if (current > 0 ){
			--current;

			auto m = changes[current];
			balance = m->balance;

			return m;
		}

		return std::make_shared<Memento>();
	}

	std::shared_ptr<Memento> redo() {
		if (size_t(current + 1) < changes.size()) {
			++current;
			auto m = changes[current];
			balance = m->balance;
			return m;
		}

		return std::make_shared<Memento>();
	}

	friend std::ostream& operator<<(std::ostream& os, const BankAccount& account) {
		os << "balance: " << account.balance;
		return os;
	}
};
int main() {

	BankAccount ba{ 100 };
	ba.deposit(50);
	ba.deposit(25);

	std::cout << ba << std::endl;


	ba.undo();
	std::cout << "Undo 1: " << ba << std::endl;

	ba.undo();
	std::cout << "Undo 2: " << ba << std::endl;

	ba.redo();
	std::cout << "Undo: " << ba << std::endl;
	return 0;
}
