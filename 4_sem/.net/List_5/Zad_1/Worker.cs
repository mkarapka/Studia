
namespace Bench
{
    public class Worker
    {
        public int DoWork(int x, int y)
        {
            return x + y;
        }

        public dynamic DoWork2(dynamic x, dynamic y)
        {
            return x + y;
        }

        public int DoComplexWork(int x, int y)
        {
            int op(int x, int y)
            {
                return x * x * x * x + y * (x - y) * x + y * y * (y - x) * x * y;
            }

            int sum = 0;
            for (int i = 0; i <= x; i++)
            {
                sum += op(i, y);
            }
            return sum;
        }

        public dynamic DoComplexWork2(dynamic x, dynamic y)
        {
            dynamic op(dynamic x, dynamic y)
            {
                return x * x * x * x + y * (x - y) * x + y * y * (y - x) * x * y;
            }

            dynamic sum = 0;
            for (dynamic i = 0; i <= y; i++)
            {
                sum += op(i, y);
            }
            return sum;
        }
    }
}