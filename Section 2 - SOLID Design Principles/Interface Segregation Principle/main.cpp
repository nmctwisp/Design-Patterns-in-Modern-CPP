#include <vector>

// Interface Segregation Principle : Clients should not be forced to depend upon interfaces that they do not use.

struct Document;

//struct IMachine
//{
//  virtual void print(Document& doc) = 0;
//  virtual void fax(Document& doc) = 0;
//  virtual void scan(Document& doc) = 0;
//};
//
//struct MFP : IMachine
//{
//  void print(Document& doc) override;
//  void fax(Document& doc) override;
//  void scan(Document& doc) override;
//};

// 1. Recompile
// 2. Client does not need this
// 3. Forcing implementors to implement too much

struct IPrinter {
	virtual void print(Document& doc) = 0;
};

struct IScanner {
	virtual void scan(Document& doc) = 0;
};

struct IFaxMachine {
	virtual void fax(Document& doc) = 0;
};

struct Printer : public IPrinter {
	void print(Document& doc) override {};
};

struct Scanner : public IScanner {
	void scan(Document& doc) override {};
};

struct FaxMachine : public IFaxMachine {
	void fax(Document& doc) override {};
};

struct IMachine : IPrinter, IScanner, IFaxMachine {
};

struct Machine : public IMachine {
	IPrinter& printer;
	IScanner& scanner;
	IFaxMachine& fax_machine;

	Machine(IPrinter& printer, IScanner& scanner, IFaxMachine& fax)
		: printer{ printer }, scanner{ scanner }, fax_machine{fax} {}

	void print(Document& doc) override {
		printer.print(doc);
	}

	void scan(Document& doc) override {
		scanner.scan(doc);
	}

	void fax(Document& doc) override {
		fax_machine.fax(doc);
	}
};


int main() {
	Printer p{};
	Scanner s{};
	FaxMachine f{};
	Machine m{ p, s , f};
}