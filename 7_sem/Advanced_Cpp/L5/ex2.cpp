#include <forward_list>
#include <iostream>
#include <string>
#include <cctype>
#include <span>
#include <optional>
#include <tuple>
#include <map>
#include <unordered_map>
#include <deque>
#include <cmath>
#include <stack>

using namespace std;

auto tokenize(const string& txt)
{
    forward_list<span<const char>> tokens;
    size_t start = 0;
    size_t end = 0;
    while(end < txt.size())
    {
        while(end < txt.size() && isspace(txt[end]))
            ++end;
        start = end;
        while(end < txt.size() && !isspace(txt[end]))
            ++end;
        if(start < end)
        {
            tokens.emplace_front(&txt.data()[start], end - start);
        }
    }
    return tokens;
}

enum class SymbolType
{
    Number,
    Variable,
    Constant,
    Function,
    Operator,
    LeftP,
    RightP
};

using Symbol = 
    tuple<SymbolType, 
        optional<double>, /*opt number value*/ 
        optional<string>, /*opt string name for consts, funcs, variables*/ 
        int               /*priority for operators*/>;

map<string, double> constants = {
    {"pi", 3.14159},
    {"e", 2.71828}
};

unordered_map<string, double> variables;

deque<string> operators_and_functions = {
    "+", "-", "*", "/", "^",
    "sin", "cos", "tan", "log", "exp"
};

forward_list<Symbol> parseTokens(const auto& tokens)
{
    forward_list<Symbol> symbols;
    for(const auto& t : tokens)
    {
        string token_str(t.data(), t.size());

        if (constants.contains(token_str)) {
            symbols.emplace_front(SymbolType::Constant, constants[token_str], token_str, 0);
        }
        else if (variables.contains(token_str)) {
            symbols.emplace_front(SymbolType::Variable, variables[token_str], token_str, 0);
        }
        else if (find(operators_and_functions.begin(), 
            operators_and_functions.end(), token_str) != operators_and_functions.end()) 
        {
            int priority = 0;
            if (token_str == "+" || token_str == "-") priority = 1;
            else if (token_str == "*" || token_str == "/") priority = 2;
            else if (token_str == "^") priority = 3;
            else priority = 4;
            symbols.emplace_front(SymbolType::Operator, nullopt, token_str, priority);
        }
        else if (token_str == "(") {
            symbols.emplace_front(SymbolType::LeftP, nullopt, nullopt, 0);
        }
        else if (token_str == ")") {
            symbols.emplace_front(SymbolType::RightP, nullopt, nullopt, 0);
        }
        else {
            double num = stod(token_str);
            symbols.emplace_front(SymbolType::Number, num, nullopt, 0);
        }
    }
    return symbols;
}

forward_list<Symbol> convertSymbolsIntoRPN(const forward_list<Symbol>& symbols)
{
    forward_list<Symbol> output;
    stack<Symbol> op_stack;
    auto outputIt = output.before_begin();

    for(const auto& sym : symbols)
    {
        auto [type, value, name, priority] = sym;
        switch(type)
        {
            case SymbolType::Number:
            case SymbolType::Variable:
            case SymbolType::Constant:
                outputIt = output.insert_after(outputIt, sym);
                break;
            case SymbolType::Function:
                op_stack.push(sym);
                break;
            case SymbolType::Operator:
                while(!op_stack.empty())
                {
                    auto [top_type, top_value, top_name, top_priority] = op_stack.top();
                    if((top_type == SymbolType::Operator && top_priority >= priority) ||
                       (top_type == SymbolType::Function))
                    {
                        outputIt = output.insert_after(outputIt, op_stack.top());
                        op_stack.pop();
                    }
                    else
                    {
                        break;
                    }
                }
                op_stack.push(sym);
                break;
            case SymbolType::LeftP:
                op_stack.push(sym);
                break;
            case SymbolType::RightP:
                while(!op_stack.empty() && get<0>(op_stack.top()) != SymbolType::LeftP)
                {
                    outputIt = output.insert_after(outputIt, op_stack.top());
                    op_stack.pop();
                }
                if(!op_stack.empty() && get<0>(op_stack.top()) == SymbolType::LeftP)
                {
                    op_stack.pop();
                }
                break;
        }
    }

    while(!op_stack.empty())
    {
        outputIt = output.insert_after(outputIt, op_stack.top());
        op_stack.pop();
    }

    return output;
}

void printRPN(const forward_list<Symbol>& rpn)
{
    for(const auto& [type, value, name, priority] : rpn)
    {
        switch(type)
        {
            case SymbolType::Number:
                if (value) cout << *value << " ";
                break;
            case SymbolType::Constant: 
            case SymbolType::Function: 
            case SymbolType::Operator: 
            case SymbolType::Variable:
                if (name) cout << *name << " ";
                break;
            default:
                break;
        }
    }
}

int main()
{
    string equation = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
    auto tokens = tokenize(equation);
    auto symbols = parseTokens(tokens);
    auto rpn = convertSymbolsIntoRPN(symbols);
    printRPN(rpn);
}