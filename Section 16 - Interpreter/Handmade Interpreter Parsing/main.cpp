#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <boost/lexical_cast.hpp>

struct Token {
	enum class Type {
		integer = 0,
		plus = 1,
		minus = 2,
		lparen = 3,
		rparen = 4
	} type;

	std::string text;

	Token(Type type, const std::string& text)
		: type(type), text(text) {};

	friend std::ostream& operator<<(std::ostream& os, const Token& token) {

		os << "'" << token.text << "'";

		return os;
	}
};

std::vector<Token> lex(const std::string& input) {
	std::vector<Token> result;
	char text;
	for (unsigned int i = 0; i < input.size(); i++) {
		text = input[i];

		switch (text) {
		case '+':
			result.push_back(Token{ Token::Type::plus, std::string{text} });
			break;
		case '-':
			result.push_back(Token{ Token::Type::minus, std::string{text} });
			break;
		case '(':
			result.push_back(Token{ Token::Type::lparen, std::string{text} });
			break;
		case ')':
			result.push_back(Token{ Token::Type::rparen, std::string{text} });
			break;
		default:
			std::ostringstream buffer;
			buffer << text;

			char next_text;
			for (unsigned int j = i + 1; j < input.size(); ++j) {
				next_text = input[j];

				if (std::isdigit(next_text)) {
					buffer << next_text;
					++i;
				}
				else {
					result.push_back(Token{ Token::Type::integer, buffer.str() });
					break;
				}
			}

		}

	}

	return result;
}

struct Element {
	virtual int eval() const = 0;
};

struct Integer : Element {
	int value;

	Integer(int value) : value(value) {};

	int eval() const override {
		return value;
	};
};

struct BinaryOperation : Element {

	std::shared_ptr<Element> lhs;
	std::shared_ptr<Element> rhs;

	enum class Type {
		addition = 0,
		subtraction = 1
	} type;

	int eval() const override {
		auto left_value = lhs->eval();
		auto right_value = rhs->eval();

		if (type == Type::addition)
			return left_value + right_value;
		else
			return left_value - right_value;
	};

};

std::shared_ptr<Element> parse(const std::vector<Token>& tokens) {
	auto result = std::make_unique<BinaryOperation>();
	auto have_lhs{ false };

	for (unsigned int i = 0; i < tokens.size(); i++) {
		auto& token = tokens[i];

		switch (token.type) {
		case Token::Type::integer: {
			int value = boost::lexical_cast<int>(token.text);
			std::shared_ptr<Integer> integer = std::make_shared<Integer>(value);

			if (!have_lhs) {
				result->lhs = integer;
				have_lhs = true;
			}
			else
				result->rhs = integer;
			break;
		}
		case Token::Type::plus: {
			result->type = BinaryOperation::Type::addition;
			break;
		}
		case Token::Type::minus: {
			result->type = BinaryOperation::Type::subtraction;
			break;
		}
		case Token::Type::lparen: {
			int j = i;
			for (; j < tokens.size(); ++j)
				if (tokens[j].type == Token::Type::rparen)
					break;

			std::vector<Token> subexpression(&tokens[i + 1], &tokens[j]);
			auto element = parse(subexpression);

			if (!have_lhs) {
				result->lhs = element;
				have_lhs = true;
			}
			else
				result->rhs = element;

			i = j;
			break;
		}
								
		}
	}

	return result;

}

int main() {

	std::string expression{ "(13-4)-(12+1)" };

	auto tokens = lex(expression);

	for (auto& token : tokens) {
		std::cout << token << "  ";
	}
	std::cout << std::endl;


	try {
		auto parsed = parse(tokens);
		std::cout << expression << " = " << parsed->eval() << std::endl;
	}
	catch (std::exception err) {
		std::cout << err.what() << std::endl;
	}

	return 0;
}