namespace Zad2
{
    using System.Dynamic;
    using System.Linq.Expressions;

    public class SuperDynamic : DynamicObject
    {
        // a)
        private Dictionary<string, Object> dictionary = new Dictionary<string, object>();
        public override bool TryGetMember(GetMemberBinder binder, out object? result)
        {
            string name = binder.Name.ToLower();

            return dictionary.TryGetValue(name, out result);
        }

        public override bool TrySetMember(SetMemberBinder binder, object value)
        {
            dictionary[binder.Name.ToLower()] = value;
            return true;
        }

        // b)
        public override bool TrySetIndex(
            SetIndexBinder binder, object[] indexes, object value)
        {
            int index = (int)indexes[0];

            if (dictionary.ContainsKey(index.ToString()))
            {
                dictionary[index.ToString()] = value;
            }
            else
            {
                dictionary.Add(index.ToString(), value);
            }
            return true;
        }

        public override bool TryGetIndex(GetIndexBinder binder, object[] indexes, out object result)
        {
            int index = (int)indexes[0];
            if (dictionary.ContainsKey(index.ToString()))
            {
                return dictionary.TryGetValue(index.ToString(), out result);
            }
            else
            {
                result = null;
                return false;
            }


        }

        // c)
        public override bool TryInvoke(InvokeBinder binder, object[] args, out object result)
        {
            if (args.Length == 1 && args[0] is string methodName)
            {
                Console.WriteLine($"Method {methodName} has been executed");
                result = null;
                return true;
            }
            result = null;
            return false;
        }

        public override bool TryInvokeMember(InvokeMemberBinder binder, object[] args, out object? result)
        {
            if (binder.Name == "SumOf")
            {
                int sum = 0;
                foreach (var elem in args)
                {
                    if (elem.GetType() == typeof(int))
                    {
                        sum += (int)elem;
                    }
                    else
                    {
                        result = null;
                        return false;
                    }
                }
                result = sum;
                return true;
            }
            result = null;
            return false;
        }

        //d)
        public override bool TryUnaryOperation(UnaryOperationBinder binder, out object result)
        {
            if (binder.Operation == ExpressionType.Negate)
            {
                if (dictionary.TryGetValue("Value", out object value))
                {
                    if (value is int intValue)
                    {
                        result = -intValue;
                        return true;
                    }
                }
            }
            result = null;
            return false;
        }

        public override bool TryBinaryOperation(BinaryOperationBinder binder, object arg, out object result)
        {
            if (binder.Operation == ExpressionType.Add)
            {
                if (dictionary.TryGetValue("Value", out object value) && arg is int otherValue)
                {
                    if (value is int intValue)
                    {
                        result = intValue + otherValue;
                        return true;
                    }
                }
            }
            result = null;
            return false;
        }
    }



    class Program_2
    {
        public static void Main(string[] args)
        {
            dynamic person = new SuperDynamic();

            //a)
            person.Name = "Johnny";
            Console.WriteLine($"{person.Name}");

            person.Surname = "Depp";
            Console.WriteLine($"{person.Name} {person.Surname}");

            person.Name = "Jack";
            Console.WriteLine($"{person.Name} {person.Surname}");

            person.Surname = "Sparrow";
            Console.WriteLine($"{person.Name} {person.Surname}");

            //b)
            person[0][1] = 1;
            person[2] = 1;
            Console.WriteLine($"{person[0]} {person[2]}");

            //c)
            person("siema");
            Console.WriteLine(person.SumOf(1, 2, 3, 4, 5, 6));

            //d)
            person = 1;
            person = -person;
            person += 20;
            Console.WriteLine(person);
        }
    }
}