#include <iostream>
#include <vector>

struct BankAccount{
	int balance{ 0 };
	int overdraft_limit{ -500 };

	void deposit(int amount) {
		balance += amount;

		std::cout << "deposited: " << amount;
		std::cout << ", balance is now: " << balance << std::endl;
	};

	void withdraw(int amount) {
		if (balance - amount >= overdraft_limit) {
			balance -= amount;

			std::cout << "withdrew: " << amount;
			std::cout << ", balance is now: " << balance << std::endl;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const BankAccount& acct) {
		os << "balance: " << acct.balance;

		return os;

	}
};

struct Command {
	virtual void call() = 0;
};

struct BankAccountCommand : Command {
	BankAccount& account;
	int amount;

	enum class Action {
		deposit = 0,
		withdraw = 1,
	} action;

	BankAccountCommand(BankAccount& account, Action action, int amount)
		: account(account), action(action), amount(amount) {};

	void call() override {
		switch (action) {
		case Action::deposit:
			account.deposit(amount);
			break;
		case Action::withdraw:
			account.withdraw(amount);
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

	std::cout << ba << std::endl;
	return 0;
}