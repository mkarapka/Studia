using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Worker
{
    internal class Class2
    {
        public bool longIsPrime(int a)
        {
            for(int i = 2; i < a; i++)
            {
                if(a % i == 0)
                {
                    return false;
                }
            }
            return true;
        }
    }
}
