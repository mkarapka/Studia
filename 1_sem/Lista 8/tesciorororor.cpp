#include<iostream>
#include<cmath>
using namespace std;
bool pierwsza(int a){
    if(a==2)return true;
    if(a%2==0){
        return false;
    }
    for(int i=3; i <= sqrt(a); i+=2){
        if(a%i==0)return false;
    }
    return true;
}
int main(){
    int DolPrzedzialu, GoraPrzedzialu, NajwiekdzaPierwsza, NajmniejszaPierwsza, Nmax, Nmin, Przedzial;
    cout << "Podaj dolna granice przedzialu: ";
    cin >> DolPrzedzialu;
    cout << "Podaj gorna granice przedzialu: ";
    cin >> GoraPrzedzialu;

    if(DolPrzedzialu<2)DolPrzedzialu=2;

    bool *Liczby = new bool[GoraPrzedzialu+1];
    for(int i=0; i<=GoraPrzedzialu; i++)
        Liczby[i]=true;

    //Sito Eratosetnesa
    int j=0;
    for(int i=2; i<=GoraPrzedzialu; i++){
        if(Liczby[i]==true){
            if(pierwsza(2+j)==true){
                Liczby[i]=true;
                NajwiekdzaPierwsza=2+j;
            }
            else{
                for(int k=i; k<=GoraPrzedzialu; k += j+2)
                    Liczby[k]=false;
            }
        }
        j++;
    }
    for(int i=GoraPrzedzialu; i>=DolPrzedzialu; i--){
        if(Liczby[i])NajmniejszaPierwsza = i;
    }
    Nmin = (int)log10(NajmniejszaPierwsza)+1;
    Nmax = (int)log10(NajwiekdzaPierwsza)+1;
    int **tab = new int *[Nmax-Nmin+1];
    int k1 = pow(10,Nmin-1);
    int k2 = k1;
    int k3 = k1;
    for(int i=0; i<Nmax-Nmin+1; i++){
        Przedzial = pow(10,Nmin+i)-1;
        tab[i] = new int [Przedzial];
        for(int j=0; j<Przedzial; j++){
            tab[i][j]=0;
        }

        for(int j=0; j<Przedzial-k2; j++){
            if(Liczby[k3]==true) tab[i][j]= k3;
            k3++;
        }
        k2 = k2*10;
        k3 = k2;
    }

    int k4 = Nmin;
    for(int i=0; i<Nmax-Nmin+1; i++){
        Przedzial = pow(10,Nmin+i)-1;
        cout << "Liczby " << k4 << " cyfrowe: [";
        for(int j=0; j<=Przedzial; j++){
            if((tab[i][j]!=0)&&(tab[i][j]<=NajwiekdzaPierwsza)&&(tab[i][j]>=NajmniejszaPierwsza)) cout << tab[i][j]<<", ";
        }
        cout << "]" << endl;
        k4++;
    }
    for(int i=0; i<Nmax-Nmin+1; i++)
        delete [] tab[i];
    delete [] tab;
    tab=NULL;
    return 0;
}