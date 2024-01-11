//Mikołaj Karapka - Lista 3 - Zad 4 - Program testujący klase Wektor 

//Instrukcja kompilacji
//System: Windows
//Użyte środowisko: Mono
//Polecenia użyte do kompilacji: 
//mcs Wektor.cs -target:library -out:Wektor.dll
//mcs Program_2.cs -r:Wektor.dll
//Polecenie do uruchomienia programu: mono Program.exe

using System;
namespace L_3_Zad_4
{
    class Program
    {
        static void Main(string[] args)
        {
            //tworzenie dwóch wektorów o wymiarze 3
            Wektor wektor1 = new Wektor(3);
            wektor1.vektor[0] = 1;
            wektor1.vektor[1] = 2;
            wektor1.vektor[2] = 3;

            Wektor wektor2 = new Wektor(3);
            wektor2.vektor[0] = 4;
            wektor2.vektor[1] = 5;
            wektor2.vektor[2] = 6;

            //dodawanie dwóch wektorów
            Wektor wynik1 = wektor1 + wektor2;

            //wypisanie wyniku dodawania
            Console.Write("Wynik dodawania wektora [1,2,3] i [4,5,6]: ");
            for (int i = 0; i < wynik1.size; i++)
            {
                Console.Write(wynik1.vektor[i]);
                Console.Write(" ");
            }
            Console.WriteLine();
            Console.WriteLine();
            //iloczyn skalarny dwóch wektorów
            float wynik2 = wektor1 * wektor2;

            //wypisanie wyniku iloczynu skalarnego
            Console.WriteLine("Wynik iloczynu skalarnego wektorów [1,2,3] i " +
                              "[4,5,6]: " + wynik2);
            Console.WriteLine();
            //mnożenie wektora przez skalar
            Wektor wynik3 = wektor1 * 2;

            //wypisanie wyniku mnożenia przez skalar
            Console.Write("Wynik mnożenia wektora [1,2,3] przez skalar " +
                              "o wartości 2: ");
            for (int i = 0; i < wynik3.size; i++)
            {
                Console.Write(wynik3.vektor[i]);
                Console.Write(" ");
            }
            Console.WriteLine();
            Console.WriteLine();
            //norma wektora
            float wynik4 = wektor1.norma();

            //wypisanie wyniku normy
            Console.WriteLine("Wynik normy wektora [1,2,3]: " + wynik4);
        }
    }
}