using System;

namespace Exercise02_2
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Enter a number: ");
            int number = Convert.ToInt32(Console.ReadLine());
            
            for (int i = 0; i < 11; i++)
            {
                int operation = number * i;
                Console.WriteLine($"{number} * {i} = {operation}");
            }
        }
    }
}

