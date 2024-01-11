//Mikołaj Karapka - Lista 3 - Zad 2 - Program testujący klase MyDictionary

//Instrukcja kompilacji
//System: Windows
//Użyte środowisko: Mono
//Polecenia użyte do kompilacji: 
//mcs MyDictionary.cs -target:library -out:MyDictionary.dll
//mcs Program.cs -r:MyDictionary.dll
//Polecenie do uruchomienia programu: mono Program.exe

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyDictionaryMain
{
    class Program
    {
        static void Main(string[] args)
        {
	//nowa zmienna typu MyDictionary<string, int>
        MyDictionary<string, int> myDict = new MyDictionary<string, int>();

	//dodanie elementów do słownika
        myDict.Add("one", 1);
        myDict.Add("two", 2);
        myDict.Add("three", 3);

	//szukanie elementu o podanym kluczu
		Console.WriteLine("Wartość dla klucza 'two'");
        myDict.Search("two");
        Console.WriteLine();
	//próba dodania elementu o nieprawidłowym kluczu
		Console.WriteLine("Próba dodania elementu o kluczu two");
        myDict.Add("two", 22);
        Console.WriteLine();

	//wypisanie rozmiaru słownika przed i po dodaniu elementu 
		Console.WriteLine("Size MyDictionary przed pop: " + myDict.size);
        myDict.Pop("three");
        Console.WriteLine("Size MyDictionary po pop: " + myDict.size);
        Console.WriteLine();
        

	//szukanie elementu o podanym kluczu
		Console.WriteLine("Wartość dla klucza 'three'");
		myDict.Search("three"); 
		Console.WriteLine("Brak wartości, ponieważ dany klucz został usunięty");

		Console.ReadKey();
        }
    }
}