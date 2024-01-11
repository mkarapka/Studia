//Mikołaj Karapka, Lista 4, Zad 2: Program testujący klase SłowaFibonacciego

//Instrukcja kompilacji
//System: Windows
//Użyte środowisko: Mono
//Polecenia użyte do kompilacji: 
//mcs SłowaFibonacciego.cs -target:library -out:SłowaFibonacciego.dll
//mcs Program.cs -r:SłowaFibonacciego.dll
//Polecenie do uruchomienia programu: mono Program.exe
using System;

namespace SłowaFibonacciegoMain
{


    class Program
    {
        static void Main(string[] args)
        {
            //Wypisanie ciągu słów Fibonacciego dla wartości 10
            int i = 1;
            SłowaFibonacciego enu = new SłowaFibonacciego(10);
            foreach (var a in enu)
            {
                Console.Write($"Dla n = {i}: ");
                Console.WriteLine(a);
                i++;
            }
        }
    }
}

