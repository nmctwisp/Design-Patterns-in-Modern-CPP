#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

struct Sentence {
    std::vector<std::string> words;
    
    struct WordToken {
        bool capitalize;
    };

    std::map<size_t, WordToken> token_map;

    Sentence(const std::string& sentence) {
        std::istringstream iss( sentence );
        std::string word;

        while (std::getline(iss, word, ' ')) {
            words.push_back(word);
        }
    };

    WordToken& operator[](const size_t index) {
        token_map[index] = WordToken{};

        return token_map[index];

    }

    std::string str() const {
        std::string str;
        
        for (size_t i = 0; i < words.size(); ++i) {
            auto word = words.at(i);
            auto token = token_map.find(i);
            
            if (token != token_map.end() && token->second.capitalize)
                std::transform(word.begin(), word.end(), word.begin(), (int(&)(int)) std::toupper);
            
            if (i == words.size() - 1)
                str += word;
            else
                str += word + ' ';
        }
        return str;
    }
};

int main() {
    Sentence sentence{ "alpha beta gamma" };
    sentence[0].capitalize = true;

    std::cout << sentence.str();
};