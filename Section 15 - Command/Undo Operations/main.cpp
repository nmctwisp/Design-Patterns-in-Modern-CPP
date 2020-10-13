#include <iostream>
#include <vector>

struct BankAccount {
	int balance{ 0 };
	int overdraft_limit{ -500 };

	bool deposit(int amount) {
		balance += amount;

		std::cout << "deposited: " << amount;
		std::cout << ", balance is now: " << balance << std::endl;

		return true;
	};

	bool withdraw(int amount) {
		if (balance - amount >= overdraft_limit) {
			balance -= amount;

			std::cout << "withdrew: " << amount;
			std::cout << ", balance is now: " << balance << std::endl;

			return true;
		}
		return false;
	}

	friend std::ostream& operator<<(std::ostream& os, const BankAccount& acct) {
		os << "balance: " << acct.balance;

		return os;

	}
};

struct Command {
	bool succeeded;
	virtual void call() = 0;
	virtual void undo() = 0;
};

struct BankAccountCommand : Command {
	BankAccount& account;
	int amount;

	enum class Action {
		deposit = 0,
		withdraw = 1,
	} action;

	BankAccountCommand(BankAccount& account, Action action, int amount)
		: account(account), action(action), amount(amount) {

		succeeded = false;
	};

	void call() override {
		switch (action) {
		case Action::deposit:
			succeeded = account.deposit(amount);
			break;
		case Action::withdraw:
			succeeded = account.withdraw(amount);
			break;
		}
	}

	// Naive implementation: we're going to assume that deposit and withdrawals are symetrical
	void undo() override {
		if (!succeeded)
			return;

		switch (action) {
		case Action::deposit:
			succeeded = account.withdraw(amount);
			break;
		case Action::withdraw:
			// this is naive because withdrawal has an overdraft limit
			succeeded = account.deposit(amount);
			break;
		}
	}
};

int main() {
	BankAccount ba;
	std::vector<BankAccountCommand> commands;

	commands.emplace_back(ba, BankAccountCommand::Action::deposit, 100);
	commands.emplace_back(ba, BankAccountCommand::Action::withdraw, 200);

	std::cout << ba << std::endl;

	for (auto& cmd : commands)
		cmd.call();


	for (auto it = commands.rbegin(); it != commands.rend(); ++it)
		it->undo();

	std::cout << ba << std::endl;
	return 0;
}