#include <map>
#include <string>
#include <vector>

inline std::vector<std::string> tokenize(const std::string& input) {
    std::vector<std::string> result;
    std::string token;

    for (auto it = input.begin(); it != input.end(); ++it) {
        if (*it == '+' || *it == '-')
            result.push_back(std::string{ *it });
        else {
            token = *it;
            for (auto nit = it + 1; nit != input.end(); ++nit) {

                if (*nit == '+' || *nit == '-') {
                    break;
                }
                else {
                    token.push_back(*nit);
                    it++;
                }
            }
            result.push_back(token);
            token.clear();
        }
    }
    return result;
};

struct ExpressionProcessor
{
    std::map<char, int> variables;

    int calculate(const std::string& expression)
    {
        int result{ 0 };
        int value{ 0 };
        char current;
        std::string op;
        std::vector<std::string> tokens = tokenize(expression);          

        for (auto it = tokens.begin(); it != tokens.end(); ++it) {
            current = *it->c_str();

            if (current == '+' || current == '-'){
                op = current;
                current = *((++it)->c_str());
            }
                
            if (std::isdigit(current))
                value = std::stoi(std::string{ current });

            else if (std::isalpha(current) && it->size() == 1) {
                value = variables[current];
            }
            else
                return 0;

            if (*it == tokens.front()){
                result += value;
                continue;
            }

            if (op == "+")
                result += value;
            else
                result -= value;
        }
        return result;
    }
};