using System;

namespace Exercise02_6
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Enter a digit: ");
            int digit = Convert.ToInt32(Console.ReadLine());
            
            for (int i = 0; i < 2; i++)
            {
                Console.WriteLine("{0} {0} {0} {0}\n{0}{0}{0}{0}", digit);
            }
        }
    }
}

