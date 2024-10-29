using Bench;
using BenchmarkDotNet.Running;

public class Program_1
{
    public static void Main(string[] args)
    {
        BenchmarkRunner.Run<MyBenchmark>();
    }
}