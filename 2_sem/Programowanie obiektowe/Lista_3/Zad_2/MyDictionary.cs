//Mikołaj Karapka, lista 3, zadanie 2: Implementacja klasy MyDictionary

using System;
using System.Collections.Generic;

//zadeklarowanie klasy MyDictionary
public class MyDictionary<K,V>
{
    //zadeklarowanie zmiennej size i tablicy typu <K,V>
    public int size = 0;
    public KeyValuePair<K, V>[] tab;
    
    //konstruktor pustej tablicy 
    public MyDictionary()
    {
        tab = new KeyValuePair<K,V>[0];
    }

    //metoda, która dodaje nowy element do tablicy
    public void Add(K aKey, V aValue)
    {
        bool flag = false;
        //sprawdzanie, czy podany klucz jest unikatowy
        for (int i = 0; i < size; i++)
        {
            if (tab[i].Key.Equals(aKey))
            {
                //jeżeli nie jest, to ustawiamy flage na prawda i kończymy pętle
                flag = true;
                break;
            }
        }
        
        //jeżeli klucz jest unikatowy to wchodzimy w warunek
        if(flag == false)
        {
            //tworzymy nową tablicę o wielkości o 1 większej od poprzedniej 
            KeyValuePair<K,V> [] new_tab = new KeyValuePair<K, V>[size+1];
            int i = 0;
            
            //kopiowanie elementów starej tablicy
            while (i < size)
            {
                new_tab[i] = new KeyValuePair<K, V>(tab[i].Key, tab[i].Value);
                i++;
            }
            
            //podstawianie nowego elementu o indeksie i
            new_tab[i] = new KeyValuePair<K, V>(aKey, aValue);
            
            //ustawienie referenecji starej tablicy na nową
            tab = new_tab;
            size++;
        }
        else
        {
            //w razie błędu wypisanie, że klucz nie był unikatowy 
            Console.WriteLine("Duplicated key!");
        }
    }
    
    //metoda do wyszukiwania wartości według klucza
    public void Search(K aKey)
    {
        bool flag = false;
        
        //pętla, która sprawdza, czy dany indeks jest równy szukanej wartości 
        for (int i = 0; i < size; i++)
        {
            if (tab[i].Key.Equals(aKey))
            {
                
                //jeśli tak, to wypisujemy daną wartość 
                Console.WriteLine(tab[i].Value);
                flag = true;
                break;
            }
        }
        
        if (flag == false)
        {
            Console.WriteLine("Not found value for the given key");
        }
    }

    //metoda do usuwania danego elementu za pomocą klucza
    public void Pop(K aKey)
    {
        //zadeklarowanie tymczasowej tablicy o wielkości o 1 mniejszej od starej
        KeyValuePair<K, V>[] new_tab = new KeyValuePair<K, V>[size - 1];
        int j = 0;
        bool flag = false;
        
        //pętla do szukania danego klucza
        for (int i = 0; i < size; i++)
        {
            
            //jeżeli klucz w i-tym indeksie jest różny, to kopiujemy i-ty element
            if (!tab[i].Key.Equals(aKey))
            {
                new_tab[j] = new KeyValuePair<K, V>(tab[i].Key, tab[i].Value);
                j++;
            }
            else
            {
                //w przeciwnym przypadku ustawiamy flagę na true 
                flag = true;
            }
        }
        if (flag == true)
        {
            //jeżeli flaga jest prawdziwa, to przypisujemy adres starej tablicy
	// na nowy
            tab = new_tab;
            size--;
        }
        else
        {
            //w przeciwnym przypadku adres nowej tablicy ustawiamy na null
            new_tab = null;
        }
    }
}