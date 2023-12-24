#pragma once
#include <numeric>
#include<math.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <stdexcept>
namespace obliczenia{

class Wymierne
{
private:
    int licznik;
    int mianownik; 
public:

    Wymierne(int licznik, int mianownik);

    Wymierne(int liczba);

    Wymierne();
    
    void setWym(int licznik, int mianownik);

    int getLicz();
    int getMian();

    void nwd();

    int nww(int liczba_1, int liczba_2);

    Wymierne operator + (Wymierne wym1) ;
    Wymierne& operator += (Wymierne wym1);
    Wymierne operator - (Wymierne wym1) ;
    Wymierne& operator -= (Wymierne wym1);
    Wymierne operator * (Wymierne wym1) ;
    Wymierne& operator *= (Wymierne wym1);
    Wymierne operator / (Wymierne wym1) ;
    Wymierne& operator /= (Wymierne wym1);
    Wymierne operator - () ;
    Wymierne operator ! () ;
    int operator ++() ;
    double operator --() ;

};
void to_str(Wymierne& wym);

};



class wyjatek_wymierny : public std::logic_error {
public:
    wyjatek_wymierny(const std::string& msg) : std::logic_error(msg) {}
};

class przekroczenie_zakresu : public wyjatek_wymierny {
public:
    przekroczenie_zakresu(const std::string& msg) : wyjatek_wymierny(msg) {}
};

class dzielenie_przez_0 : public wyjatek_wymierny {
public:
    dzielenie_przez_0(const std::string& msg) : wyjatek_wymierny(msg) {}
};

class blad_wymierny : public wyjatek_wymierny {
public:
    blad_wymierny(const std::string& msg) : wyjatek_wymierny(msg) {}
};
