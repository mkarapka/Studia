//Mikołaj Karapka - LIsta 3 - Zad 4 - Implementacja klasy Wektor

using System;
using System.Configuration;
namespace L_3_Zad_4
{
    //zadelklarowanie kalsy Wektor
    public class Wektor
    {
        //zdefiniowanie zmiennej size i tablicy vektor
        public int size = 0;
        public float [] vektor;
        
        //zdefiniowanie konstruktora do ustawiania wymiaru i tworzenia nowej
        //tablicy vektor
        public Wektor(int aSize)
        {
            size = aSize;
            vektor = new float[aSize];
        }

        //zdefiniowanie operatora dodawania wektorów A i B
        public static Wektor operator +(Wektor A, Wektor B)
        {
            Wektor Result = new Wektor(A.size);
            //Tworzenie nowej tablicy typu float 
            float [] result_tab  = new float[A.size];
            
            //Przypisywanie na i-tym elemencie nowej tablicy sume
            //i-tego elementu A i B
            for (int i = 0; i < A.size; i++)
            {
                result_tab[i] = A.vektor[i] + B.vektor[i];
            }

            //przypisanie do tablicy wektora A tablice wynikową
            Result.vektor = result_tab;
            return Result;
        }

        
        //zdefiniowanie operatora iloczynu skalarnego wektorów
        public static float operator *(Wektor A, Wektor B)
        {
            float skalar_res = 0;
            
            //dodawanie do zmiennej skalar iloczynu na 
            //kolejnych elementach A i B
            for (int i = 0; i < A.size; i++)
            {
                skalar_res += A.vektor[i] * B.vektor[i];
            }

            return skalar_res;
        }

        //zdefiniowanie operatora mnożenia wektora przez skalar
        public static Wektor operator *(Wektor A, float Skalar)
        {
            
            //monożenie danego skalaru po wszystkich elementach z talblicy
            //A.vektor
            for (int i = 0; i < A.size; i++)
            {
                A.vektor[i] *= Skalar;
            }

            return A;
        }

        //zdefiniowanie metody norma()
        public float norma()
        {
            float sum = 0;
            
            //dodawanie do sumy kolejnych kwadratów na i-tym elemencie
            for (int i = 0; i < size; i++)
            {
                sum += vektor[i] * vektor[i];
            }

            return sum;
        }
    }
}