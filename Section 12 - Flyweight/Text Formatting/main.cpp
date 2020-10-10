#include <string>
#include <vector>
#include <iostream>

class FormattedText {
private:
	std::string plain_text;
	bool* caps;
public:
	FormattedText(const std::string& plain_text) : plain_text(plain_text) {
		caps = new bool[plain_text.length()];
		std::memset(caps, 0, plain_text.length());
	};

	~FormattedText() { delete caps; };

	friend std::ostream& operator<<(std::ostream& os, const FormattedText& formatted_text);

	void capitalize(int start, int end) {
		for (auto i = start; i <= end; i++) {
			caps[i] = true;
		}
	}
};

std::ostream& operator<<(std::ostream& os, const FormattedText& formatted_text) {
	std::string s;

	for (unsigned int i = 0; i < formatted_text.plain_text.length(); i++) {
		char c = formatted_text.plain_text[i];
		
		s += (formatted_text.caps[i] ? std::toupper(c) : c);
	}
	
	os << s;

	return os;
};

class BetterFormattedText {
public:
	struct TextRange;
private:
	
	std::string plain_text;
	std::vector<TextRange> formatting;
public:
	struct TextRange {
		int start;
		int end;
		bool capitalize; // bold, italic

		bool covers(int position) const { return position >= start && position <= end; };
	};

	TextRange& get_range(int start, int end) {
		formatting.emplace_back(TextRange{ start, end });

		return *(formatting.rbegin());
	}

	BetterFormattedText(const std::string& plain_text) : plain_text(plain_text) {};

	friend std::ostream& operator<<(std::ostream& os, const BetterFormattedText& formatted_text);
};

std::ostream& operator<<(std::ostream& os, const BetterFormattedText& formatted_text) {
	std::string s;

	for (unsigned int i = 0; i < formatted_text.plain_text.length(); i++) {
		auto c = formatted_text.plain_text[i];

		for (const auto& rng : formatted_text.formatting) {
			if (rng.covers(i) && rng.capitalize)
				c = std::toupper(c);

			s += c;
		}
	}

	os << s;

	return os;
}

int main(int argc, char* argv[]){
	FormattedText ft{ "This is a brave new world" };
	ft.capitalize(10, 15);
	std::cout << ft << std::endl;

	BetterFormattedText bft{ "This is a brave new world" };
	bft.get_range(10, 15).capitalize = true;
	std::cout << bft << std::endl;
}