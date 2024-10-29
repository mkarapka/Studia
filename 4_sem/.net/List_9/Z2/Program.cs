using System;
using System.Collections.Generic;
using System.Threading;

class Program
{
    private static Semaphore customers = new Semaphore(0, 100); // liczba klientów
    private static Semaphore barber = new Semaphore(0, 1); // golibroda
    private static Mutex seat = new Mutex(); // miejsce siedzące
    private static int waitingCustomers = 0; // liczba czekających klientów
    private const int numberOfSeats = 3; // liczba dostępnych miejsc

    static void Main(string[] args)
    {
        Thread barberThread = new Thread(Barber);
        barberThread.Start();

        Random rand = new Random();
        for (int i = 0; i < 10; i++)
        {
            Thread customerThread = new Thread(Customer);
            customerThread.Start();
            Thread.Sleep(rand.Next(500, 4000)); // nowy klient przychodzi co jakiś czas
        }

        barberThread.Join();
    }

    private static void Barber()
    {
        while (true)
        {
            Console.WriteLine("Golibroda zasypia.");
            Thread.Sleep(500);
            customers.WaitOne(); // czeka na klienta
            Console.WriteLine("Golibroda budzi się.");
            Thread.Sleep(500);
            seat.WaitOne();
            waitingCustomers--;
            barber.Release(); // gotowy do golenia
            seat.ReleaseMutex();
            Console.WriteLine("Golibroda strzyże klienta.");
            Thread.Sleep(3000); // czas strzyżenia
            Console.WriteLine("Golibroda skończył strzyżenie.");
        }
    }

    private static Queue<int> waitingCustomersQueue = new Queue<int>(); // kolejka klientów

    private static void Customer()
    {
        seat.WaitOne();
        if (waitingCustomersQueue.Count < numberOfSeats)
        {
            waitingCustomersQueue.Enqueue(Thread.CurrentThread.ManagedThreadId); // dodaj ID wątku do kolejki
            Console.WriteLine("Klient siada w poczekalni. Czekających klientów: " + waitingCustomersQueue.Count);
            customers.Release(); // powiadom golibrodę
            seat.ReleaseMutex();
            barber.WaitOne(); // czeka na strzyżenie
            Console.WriteLine("Klient jest strzyżony.");
            waitingCustomersQueue.Dequeue(); // usuń ID wątku z kolejki
        }
        else
        {
            Console.WriteLine("Brak miejsca, klient odchodzi.");
            seat.ReleaseMutex();
        }
    }
}
