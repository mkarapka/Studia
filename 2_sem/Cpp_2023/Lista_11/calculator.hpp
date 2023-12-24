#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<typeinfo>
#include "types.hpp"
#include "funkcje.hpp"
namespace kalkulator {

    bool isNumber(std::string& token);

    bool isVariable(const std::string& token);

    bool isConstant(const std::string& token);

    bool isOperator(const std::string& op, std::queue<Symbol*>& symbols);

    std::queue<Symbol*> parse(const std::vector<std::string>& LsExp);

    double eval(std::queue<Symbol*>& Exp); 
    
    bool OpEval( std::stack<Symbol*>& calc,  Symbol* op);

};