using System;

namespace Two
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Enter first integer: ");
            int a = Convert.ToInt32(Console.ReadLine());

            Console.Write("Enter second integer: ");
            int b = Convert.ToInt32(Console.ReadLine());

            Console.Write("Enter third integer: ");
            int c = Convert.ToInt32(Console.ReadLine());

            int max = Math.Max(Math.Max(a, b), c);
            int min = Math.Min(Math.Min(a, b), c);
            int sum = a + b + c;
            int product = a * b * c;
            double average = Convert.ToDouble(a + b + c) / 3;
            
            average = Math.Round(average, 3);

            Console.WriteLine($"For the numbers {a}, {b}, {c}");
            Console.WriteLine($"Largest is {max}");
            Console.WriteLine($"Smallest is {min}");
            Console.WriteLine($"Sum is {sum}");
            Console.WriteLine($"Product is {product}");
            Console.WriteLine($"Average is {average}");
        }
    }
}

