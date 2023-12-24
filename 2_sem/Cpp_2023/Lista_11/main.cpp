#include <iostream>
#include <sstream>
#include <vector>
#include "calculator.hpp"
#include "funkcje.hpp"
int main() {
    std::string input, s_exp;
    int size_in;
    std::vector<std::string> listof_sExp;
    while (input != "exit")
    {
        std::getline(std::cin, input);
        size_in = input.size();
        if(input.find("print") != std::string::npos){
            int j = 1;
            while(input[j-1] != ' '){
                j++;
            }
            
            for (int i = j; i < size_in; i++) 
            {
                if(input[i] != ' '){
                    s_exp += input[i];
                }
                else if(input[i] == ' '){
                    listof_sExp.push_back(s_exp);
                    s_exp.clear();
                }
            }
            if (!s_exp.empty()) {
                listof_sExp.push_back(s_exp);
                s_exp.clear();
            }
            std::queue<kalkulator::Symbol*> costam = kalkulator::parse(listof_sExp);
            
            double value = kalkulator::eval(costam);
            std::cout << value << std::endl;
            listof_sExp.clear();
        }
        
        else if(input.find("set") != std::string::npos and 
                input.find("to") != std::string::npos){
            std::string variable[2];
            int j = 0;
            for (int i = 0; i < size_in; i++) 
            {
                if(input[i] != ' '){
                    s_exp += input[i];
                }
                else if(s_exp == "set" or s_exp == "to"){
                    s_exp += input[i];
                    s_exp.clear();
                }
                else if(input[i] == ' '){
                    if(kalkulator::isVariable(s_exp)){
                        variable[j] = s_exp;
                        j++; 
                    }
                    s_exp.clear();
                }
            }
            if (!s_exp.empty()) {
                variable[j] = s_exp;
                s_exp.clear();
            }
            kalkulator::Zmienna::values[variable[0]] = std::stod(variable[1]);
        }
        else if(input == "clear"){
            kalkulator::Zmienna::values.clear();
        }
        else if(input == "exit"){
            continue;
        }
        else{
            std::clog << "Invalid input\n";
        }
    }
    return 0;
}