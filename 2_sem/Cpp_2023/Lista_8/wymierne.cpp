#include <iostream>
#include "wymierne.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
namespace obliczenia{
void Wymierne::setWym(int licznik, int mianownik){
        this->licznik = licznik;
        if(mianownik > 0){
            this->mianownik = mianownik;
        }
        else{
            throw("Zła wartość mianownika!");
        }
        nwd();
    }

Wymierne::Wymierne(int licznik, int mianownik){
        setWym(licznik, mianownik);
    }

Wymierne::Wymierne(int liczba){
        setWym(liczba,1);
    }
Wymierne::Wymierne(){
        setWym(0,1);
    }
int Wymierne::getLicz(){ return licznik;}
int Wymierne::getMian(){ return mianownik; }

void Wymierne::nwd(){
            int dziel = std::gcd(licznik,mianownik);
            licznik = licznik / dziel;
            mianownik = mianownik / dziel;
    }

int Wymierne::nww(int liczba_1, int liczba_2) {
        int result = liczba_1 * liczba_2 / std::gcd(liczba_1,liczba_2);
        return result;
    }
Wymierne Wymierne::operator +(Wymierne wym1) {
        int new_mian = nww(getMian(), wym1.getMian());
        int new_licz = (getLicz() *  (new_mian/getMian()))
        + (wym1.getLicz() * (new_mian/wym1.getMian()));
        return Wymierne(new_licz,new_mian);
    }

    Wymierne& Wymierne::operator += (Wymierne wym1){
        int new_mian = nww(getMian(), wym1.getMian());
        int new_licz = (getLicz() *  (new_mian/getMian()))
        + (wym1.getLicz() * (new_mian/wym1.getMian()));
        setWym(new_licz, new_mian);
        return *this;
    }

    Wymierne Wymierne::operator - (Wymierne wym1){
        int new_mian = nww(getMian(), wym1.getMian());
        int new_licz = (getLicz() *  (new_mian/getMian()))
        - (wym1.getLicz() * (new_mian/wym1.getMian()));
        return Wymierne(new_licz,new_mian);
    }

    Wymierne& Wymierne::operator -=(Wymierne wym1){
        int new_mian = nww(getMian(), wym1.getMian());
        int new_licz = (getLicz() *  (new_mian/getMian()))
        - (wym1.getLicz() * (new_mian/wym1.getMian()));
        setWym(new_licz, new_mian);
        return *this;
    }

    Wymierne Wymierne::operator *(Wymierne wym1) {
        int new_mian = getMian() * wym1.getMian();
        int new_licz = getLicz() * wym1.getLicz();
        return Wymierne(new_licz,new_mian);
    } 

    Wymierne& Wymierne::operator *= (Wymierne wym1){
        int new_mian = getMian() * wym1.getMian();
        int new_licz = getLicz() * wym1.getLicz();
        setWym(new_licz,new_mian);
        return *this;
    } 

    Wymierne Wymierne::operator / (Wymierne wym1) {
        int new_mian = getMian() * wym1.getLicz();
        int new_licz = getLicz() * wym1.getMian();
        return Wymierne(new_licz,new_mian);

    } 

    Wymierne& Wymierne::operator /= (Wymierne wym1){
        int new_mian = getMian() * wym1.getLicz();
        int new_licz = getLicz() * wym1.getMian();
        setWym(new_licz,new_mian);
        return *this;
    } 

    Wymierne Wymierne::operator -() {
        int mian = getMian();
        int licz = getLicz() * (-1);
        return Wymierne(licz,mian);
    }

    Wymierne Wymierne::operator !() {
        int mian = getMian();
        int licz = getLicz();
        return Wymierne(mian, licz);
    }
    
    int Wymierne::operator ++() {
        double result = (double)getLicz() / (double)getMian();
        int liczba = round(result);
        return liczba;
    }
    
    double Wymierne::operator --() {
        double result = (double)getLicz() / (double)getMian();
        return result;
    }

    void to_str(Wymierne& wym){
        std::cout << wym.getLicz() << "/" << wym.getMian() << std::endl;
    }
}

