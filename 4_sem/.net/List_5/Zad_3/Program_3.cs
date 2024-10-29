namespace Zad3
{
    using System.Runtime.CompilerServices;

    public static class TaskExtensions
    {
        public static TaskAwaiter GetAwaiter(this int miliseconds)
        {
            return Task.Delay(miliseconds).GetAwaiter();
        }
    }
    class Program_3
    {
        public async static Task PrintSome()
        {
            Console.WriteLine("a");
            await 500;
            Console.WriteLine("b");
            await 2000;
            Console.WriteLine("c");
        }
        public async static Task Main(string[] args)
        {
            Console.WriteLine("1");
            Task.WhenAll(PrintSome(), PrintSome());
            await 2000;
            Console.WriteLine("2");
        }
    }
}