#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

bool isBalanced(const std::string& code) {
    std::stack<char> bracketStack;
    std::unordered_map<char, char> matchingBrackets = {
        {')', '('},
        {'}', '{'},
        {']', '['},
        {'>', '<'},
        {'"', '"'},
        {'\'', '\''},
    };

    for (size_t i = 0; i < code.length(); ++i) {
        char current = code[i];

        if (current == '(' || current == '{' || current == '[' || current == '<' || current == '"' || current == '\'') {
            
            if ((current == '"' || current == '\'') && !bracketStack.empty() && bracketStack.top() == current) {
                bracketStack.pop();
            } else {
                bracketStack.push(current);
            }
        }
        
        else if (current == ')' || current == '}' || current == ']' || current == '>') {
            if (bracketStack.empty() || bracketStack.top() != matchingBrackets[current]) {
                return false;
            }
            bracketStack.pop();
        }
    }
   
    return bracketStack.empty();
}

int main() {
    std::string code;

    std::cout << "Enter the code to check: ";
    std::getline(std::cin, code);

    if (isBalanced(code)) {
        std::cout << "The code has balanced brackets.\n";
    } else {
        std::cout << "The code has unbalanced or mismatched brackets.\n";
    }

    return 0;
}
