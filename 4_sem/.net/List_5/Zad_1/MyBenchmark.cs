using BenchmarkDotNet.Attributes;

namespace Bench
{
    public class MyBenchmark
    {
        Worker John = new Worker();
        public int x, y;
        public int N;

        [Benchmark]
        public int TestStaticSimple()
        {
            return John.DoWork(x, y);
        }

        [Benchmark]
        public dynamic TestDynamicSimple()
        {
            return John.DoWork2(x, y);
        }

        [Benchmark]
        public int TestStaticComplex()
        {
            return John.DoComplexWork(x, y);
        }

        [Benchmark]
        public dynamic TestDynamicComplex()
        {
            return John.DoComplexWork2(x, y);
        }
    }
}