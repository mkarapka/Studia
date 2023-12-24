#pragma once
#include<unordered_map>
#include<iostream>
#include<string>
namespace kalkulator{
    class Symbol{
        public:
            virtual ~Symbol() = default;
    };

    class Operand : public Symbol{
        public:
            virtual double getValue() const = 0;
    };

    class Liczba : public Operand{
        private:
            double value;
        public:
            Liczba(double value) : value(value) {}

            double getValue() const override{
                return value;
            }
    };
    
    class Stala : public Operand {
        private:
            std::string name;
            double value;
        public:
            Stala(std::string name) : name(name){
                if(name == "e"){
                    value = 2.718281828459;
                }
                else if(name == "pi"){
                    value = 3.141592653589;
                }
                else if(name == "fi"){
                    value = 1.618033988750;
                }
                else{
                    throw("Invalid name of variable");
                }
            }

            double getValue() const override{
                return value;
            }
    };

    class Zmienna : public Operand {
    public:
        std::string name;
        static std::unordered_map<std::string, double> values;

        Zmienna(const std::string& name) : name(name) {}

        double getValue() const override {
            return values.at(name);
        }
    };

};