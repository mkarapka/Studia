#include "calculator.hpp"

namespace kalkulator{
std::unordered_map<std::string, double> kalkulator::Zmienna::values;

double kalkulator::Frac::calculate(double val1, double val2){
    double result = 1, i = 1,tmp;
    if(val1 < 0){
        std::clog << "Argument must be positive!" << std::endl;
        return -1;
    }
    while (i-1 != val1)
    {
        result *= i;
        i ++;
    }
    return result;
}

double kalkulator::Sng::calculate(double val1,double val2) {
    if(val1 > 0){
        return 1;
    }
    else if (val1 == 0){
        return 0;
    }
    else{
        return -1;
    }
}

bool isNumber(const std::string& token){
    for (int i = 0; i < token.size(); i++)
    {
        if ((token[i] < '0' || token[i] > '9') && token[i] != '.' && token[i] != '-')
        {
            return false;
        }
    }
    return true;
}

bool isVariable(const std::string& token) {
    if (token.length() <= 7 and token.length() > 0) {
        if(token.find("print") == std::string::npos && token.find("set") == std::string::npos
        && token.find("exit") == std::string::npos && token.find("to") == std::string::npos
        && token.find("clear") == std::string::npos && token != "e" && token != "pi" && token != "fi")
        {
            if(token[0] < 'a' or token[0] > 'z') {
                return false;
            }
            return true;
        }
        return false;
    }
    return false;
}

bool isConstant(const std::string& token){
    if(token == "e" or token == "pi" or token == "fi"){
        return true;
    }
    return false;
}

bool isOperator(const std::string& op, std::queue<Symbol*>& symbols){
        Funkcja *funkcja = nullptr;
        if(op == "+"){
            funkcja = new Add();
        }
        else if(op == "-"){
            funkcja = new Sub();
        }
        else if(op == "*"){
            funkcja = new Mult();
        }
        else if(op == "/"){
            funkcja = new Div();
        }
        else if(op == "%"){
            funkcja = new Modulo();
        }
        else if(op == "abs"){
            funkcja = new Abs();
        }
        else if(op == "min"){
            funkcja = new Min();
        }
        else if(op == "max"){
            funkcja = new Max();
        }
        else if(op == "pow"){
            funkcja = new Pow();
        }
        else if(op == "sng"){
            funkcja = new Sng();
        }
        else if(op == "floor"){
            funkcja = new Floor();
        }
        else if(op == "ceil"){
            funkcja = new Ceil();
        }
        else if(op == "!"){
            funkcja = new Frac();
        }
        else if(op == "sin"){
            funkcja = new Sin();
        }
        else if(op == "cos"){
            funkcja = new Cos();
        }
        else if(op == "log"){
            funkcja = new Log();
        }

        if(funkcja != nullptr){
            symbols.push(funkcja);
            return true;
        }
        return false;
    }

bool OpEval(Symbol* op){
    Funkcja* f = dynamic_cast<Funkcja*>(op);
    return f != nullptr;
}

std::queue<Symbol*> parse(const std::vector<std::string>& LsExp) 
{
    std::queue<Symbol*> symbols;
    for (int i = 0; i < LsExp.size(); i++)
    {
        if(isConstant(LsExp[i])){
            Stala *stala = new Stala(LsExp[i]);
            symbols.push(stala);
        }
        else if(isNumber(LsExp[i])){
            Liczba *liczba = new Liczba(std::stod(LsExp[i]));
            symbols.push(liczba);
        }
        else if(isOperator(LsExp[i],symbols)){
            continue;
        }
        else if(isVariable(LsExp[i])){
            Zmienna *zmienna = new Zmienna(LsExp[i]);
            symbols.push(zmienna);
        }
        else{
            std::clog << "Invalid symbol" << std::endl;
        }
    }
    return symbols;
}
 
double eval(std::queue<Symbol*>& Exp){
    std::stack<Symbol*> calc;
    double value;
    Symbol* s;
    while (!Exp.empty()) {
        s = Exp.front();
        Exp.pop();
        if(OpEval(s)){
            Funkcja* f = dynamic_cast<Funkcja*>(s);
            if(!f->isUnary()) {
                if(calc.size() < 2) {
                    std::clog << "Not enough operands for function" << std::endl;
                }
                Operand* a = dynamic_cast<Operand*>(calc.top()); calc.pop();
                Operand* b = dynamic_cast<Operand*>(calc.top()); calc.pop();
                if(a == nullptr || b == nullptr) {
                    std::clog << "Expected operands on the stack" << std::endl;
                }
                value = f->calculate(b->getValue(), a->getValue());
                calc.push(new Liczba(value));
            }
            else{
                Operand* c = dynamic_cast<Operand*>(calc.top()); calc.pop();
                value = f->calculate(c->getValue());
                calc.push(new Liczba(value));
            }
        } 
        else {
            try
            {
                Operand* o = dynamic_cast<Operand*>(s);
                if(Zmienna* z = dynamic_cast<Zmienna*>(o)){
                    calc.push(new Liczba(z->getValue()));
                } else {
                    calc.push(o);
            }
            }
            catch(const std::exception& e)
            {
                std::clog << "Missing variable assignment" << std::endl;
                return -1;
            }
            
            
        }
    }


    if(calc.size() != 1) {
        std::clog << "Expression evaluation error" << std::endl;
    }
    Operand* result = dynamic_cast<Operand*>(calc.top());
    if(result == nullptr) {
        std::clog << "Expected final value to be an operand" << std::endl;
    }


    value = result->getValue();
    delete calc.top();
    calc.pop();
    while (!Exp.empty()) {
        delete Exp.front(); 
        Exp.pop(); 
    }
    return value;
}
}
