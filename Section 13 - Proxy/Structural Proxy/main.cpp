#include <iostream>
#include <memory>
struct BankAccount {
	virtual ~BankAccount() = default;
	virtual void deposit(int amount) = 0;
	virtual void withdraw(int amount) = 0;
};

struct CurrentAccount : BankAccount {
private:
	int balance;
public:
	explicit CurrentAccount(const int balance) : balance(balance) {};

	void deposit(int amount) override { balance += amount; };

	void withdraw(int amount) override { 
		if (amount <= balance)
			balance -= amount; 
	};

	friend std::ostream& operator<<(std::ostream& os, const CurrentAccount& obj) {
		os << "balance: " << obj.balance;

		return os;
	}
};

int main() {
	BankAccount* a = new CurrentAccount(123);
	a->deposit(321);
	delete a;

	auto b = std::make_shared<CurrentAccount>(123);
	BankAccount* actual = b.get(); // enhancement

	return 0;
}