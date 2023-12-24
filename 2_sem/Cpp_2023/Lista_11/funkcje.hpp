#pragma once
#include<cmath>
#include<iostream>
#include<string>
namespace kalkulator{
    class Funkcja : public Symbol{
        public:
            virtual double calculate(double val1, double val2 = 0) = 0;
            virtual bool isUnary() = 0;
    };

    class Add : public Funkcja{
        public:
            double calculate(double val1, double val2) override {
                return val1 + val2;
            }

            bool isUnary() override{
                return false;
            }
    };    

    class Sub : public Funkcja{
        public:
            double calculate(double val1, double val2) override { 
                return val1 - val2;;
            }

            bool isUnary() override{
                return false;
            }
    };

    class Mult : public Funkcja{
        public:
            double calculate(double val1, double val2) override{
                return val1 * val2;
            }

            bool isUnary() override{
                return false;
            }
    };

    class Div : public Funkcja{
        public:
            double calculate(double val1, double val2) override {
                if (val2 != 0){
                    return val1 / val2;
                    
                }
                else{
                    throw "Division by zero!";
                }
            }

            bool isUnary() override{
                return false;
            }
    };

    class Modulo : public Funkcja{
        public:
            double calculate(double val1, double val2) override {
                return fmod(val1, val2);
            }

            bool isUnary() override{
                return false;
            }
    };
    
    class Min : public Funkcja{
        public:
            double calculate(double val1, double val2) override {
                if(val1 < val2){
                    return val1;
                }
                else{
                    return val2;
                }
            }

            bool isUnary() override{
                return false;
            }
    };

    class Max : public Funkcja{
        public:
            double calculate(double val1, double val2) override {
                if(val1 > val2){
                    return val1;
                }
                else{
                    return val2;
                }
            }

            bool isUnary() override{
                return false;
            }
    };

    class Pow : public Funkcja{
        public:
            double calculate(double val1, double val2) override {
                return pow(val1, val2);
            }

            bool isUnary() override{
                return false;
            }
    };

    class Abs : public Funkcja{
        public:
            double calculate(double val1,double val2) override {
                return abs(val1);
            }

            bool isUnary() override{
                return true;
            }
    };

    class Sng : public Funkcja{
        public:
            double calculate(double val1,double val2) override;

            bool isUnary() override{
                return true;
            }
    };

    class Floor : public Funkcja{
        public:
            double calculate(double val1,double val2) override {
                return floor(val1);
            }

            bool isUnary() override{
                return true;
            }
    };

    class Ceil : public Funkcja{
        public:
            double calculate(double val1,double val2) override {
                return ceil(val2);
            }

            bool isUnary() override{
                return true;
            }
    };

    class Frac : public Funkcja{
        public:
            double calculate(double val1, double val2) override;

            bool isUnary() override{
                return true;
            }
    };

    class Sin : public Funkcja {
    public:
        double calculate(double val1, double val2) override {
            return sin(val1);
        }

        bool isUnary() override{
            return true;
        }
    };

    class Cos : public Funkcja {
    public:
        double calculate(double val1, double val2) override {
            return cos(val1);
        }

        bool isUnary() override{
            return true;
        }
    };

    class Log : public Funkcja {
    public:
        double calculate(double val1, double val2) override {
            if (val2 <= 0) {
                throw "Logarithm base must be positive!";
            }
            return log(val1) / log(val2);
        }

        bool isUnary() override{
            return false;
        }
    };

    class Exp : public Funkcja {
    public:
        double calculate(double val1, double val2 = 0) override {
            return exp(val1);
        }

        bool isUnary() override{
            return true;
        }
    };
};