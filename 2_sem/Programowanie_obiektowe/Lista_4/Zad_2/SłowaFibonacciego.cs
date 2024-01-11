//Mikołaj Karapka, Lista 4, Zad 2: Implementacja klasy SłowaFibonacciego

using System;
using System.Collections;

//Klasa implementująca słowa ciągu Fibonacciego i umożliwiająca ich iterowanie
public class SłowaFibonacciego : IEnumerable
{
    //Wartość określająca, ile słów ciągu ma zostać wygenerowanych
    public int value; 

    //Konstruktor klasy
    public SłowaFibonacciego(int Avalue)
    {
        value = Avalue;
    }

    //Metoda zwracająca enumerator dla iterowania po słowach ciągu Fibonacciego
    public IEnumerator GetEnumerator()
    {
        return new IFibonacci(value);
    }
}

//Klasa implementująca enumerator dla słów ciągu Fibonacciego
public class IFibonacci : IEnumerator
{
    //Zadeklarowanie zmiennych t.j. drugie słowo, iterator, liczba iteracji
    //początkowa wrtość current
    private string word = "a"; 
    private int it = 0; 
    public int n; 
    private object _current = "b"; 

    //Konstruktor klasy
    public IFibonacci(int Aval)
    {
        n = Aval;
    }

    //Metoda przechodząca do kolejnego elementu
    public bool MoveNext()
    {
        //Zmienna tymczasowa
        string tmp;
        
        //Jeśli dany iterator różny od n, to przechodzimy do następnego elemnetu
        if (it != n)
        {
            if (it > 0)
            {
                //Zapisywanie poprzedniej wartości current i przypisanie
                //jej nowej wartości
                tmp = Current.ToString(); 
                Current = word; 
                word = Current.ToString() + tmp; 
            }
            it++; 
            return true;
        }

        return false;
    }

    //Metoda resetująca iterator do stanu początkowego
    public void Reset()
    {
        Current = "b"; 
    }

    //Właściwość zwracająca aktualne słowo w iteracji
    public object Current
    {
        get { return _current; }
        set { _current = value; }
    }    
}


