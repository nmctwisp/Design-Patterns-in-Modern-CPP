#include <iostream>
#include <sstream>
#include <vector>
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


int main() {

	std::string expression{ "(13-4)-(12+1)" };

	auto tokens = lex(expression);

	for (auto& token : tokens) {
		std::cout << token << "  ";
	}
	std::cout << std::endl;
	
	return 0;
}