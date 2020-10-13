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

struct CompositeBankAccountCommand : std::vector<BankAccountCommand>, Command {
	// the idea is that youwill initalized the composite bank account command with a set of commands that
	// you want to invoke and then you can call them in a single function call and you can undo them in 
	// a single function call

	CompositeBankAccountCommand(const std::initializer_list<BankAccountCommand>& cmd_lst)
		: std::vector<BankAccountCommand>(cmd_lst) {};

	void call() override {
		for (auto& cmd : *this)
			cmd.call();
	}

	void undo() override {
		for (auto it = this->rbegin(); it != this->rend(); ++it)
			it->undo();
	}
};

struct DependentCompositeCommand : CompositeBankAccountCommand {
	DependentCompositeCommand(const std::initializer_list<BankAccountCommand>& cmd_lst)
		: CompositeBankAccountCommand(cmd_lst) {};

	void call() override {
		bool ok = true;
		for (auto& cmd : *this){
			if (ok) {
				cmd.call();
				ok = cmd.succeeded;
			}
			else {
				cmd.succeeded = false;
			}
		}
			
	};

	void undo() override {
	};
};

struct MoneyTransferCommand : /*CompositeBankAccountCommand*/ DependentCompositeCommand {

	// If inheriting direct from CompositeBankAccountCommand, then this would cause
	// some unusual behavior calling this command when overdrafting, because one
	// BankAccountCommand does not know if the other BankAccountCommand succeeded.

	MoneyTransferCommand(BankAccount& from, BankAccount& to, int amount)
		: DependentCompositeCommand{
			BankAccountCommand{from, BankAccountCommand::Action::withdraw, amount},
			BankAccountCommand{to, BankAccountCommand::Action::deposit, amount}
		} {};
};

int main() {
	BankAccount ba1;
	BankAccount ba2;
	
	ba1.deposit(100);

	std::cout << "Account 1 " << ba1 << std::endl;
	std::cout << "Account 2 " << ba2 << std::endl;

	MoneyTransferCommand cmd{ ba1, ba2, 5000 };
	cmd.call();

	std::cout << "Account 1 " << ba1 << std::endl;
	std::cout << "Account 2 " << ba2 << std::endl;

	cmd.undo();

	std::cout << "Account 1 " << ba1 << std::endl;
	std::cout << "Account 2 " << ba2 << std::endl;

	return 0;
}