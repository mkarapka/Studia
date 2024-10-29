


class BarberShop
{
    static Semaphore customers = new Semaphore(0, 1000);
    static Semaphore barber = new Semaphore(0, 1);
    static Semaphore seat = new Semaphore(0, 3);
    public static int waiting_customers = 0;
    static int numberOfSeats = 3;

    
    public static void Main(string[] args)
    {
        Thread barberThread = new Thread(Barber);
        barberThread.Start();

        Random rand = new Random();
        for(int i = 0; i < 10; i++)
        {
            Thread customerThread = new Thread(Customer);
            customerThread.Start();
            Thread.Sleep(rand.Next(500, 1000));

        }
        barberThread.Join();
    }

    public static void Barber()
    {
        while (true)
        {
            Console.WriteLine("Barber idzie spać");
            customers.WaitOne();
            Thread.Sleep(500);
            Console.WriteLine("Barber budzi się");
            seat.WaitOne();
            waiting_customers--;
            barber.Release();
            seat.Release();
            Console.WriteLine("Barber strzyże klienta");
            Thread.Sleep(2000);
            Console.WriteLine("Barber skończył strzyżenie");
        }
    }

    public static void Customer()
    {
        seat.WaitOne();
        if (waiting_customers < numberOfSeats)
        {
            waiting_customers++;
            Console.WriteLine("Klient siada w poczekalni. Czekających klientów: " + waiting_customers);
            customers.Release();
            seat.Release();
            barber.WaitOne();
            Console.WriteLine("Klient jest strzyżony");
        }
        else
        {
            
            Console.WriteLine("Brak miejsca");


        }
    }
}