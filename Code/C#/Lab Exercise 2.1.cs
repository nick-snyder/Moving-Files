using System;

namespace Exercise02_1
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Input the first number: ");
            int numberOne = Convert.ToInt32(Console.ReadLine());
            
            Console.Write("Input the second number: ");
            int numberTwo = Convert.ToInt32(Console.ReadLine());
            
            int add = numberOne + numberTwo;
            int subtract = numberOne - numberTwo;
            int multiply = numberOne * numberTwo;
            int divide = numberOne / numberTwo;
            int mod = numberOne % numberTwo;

            Console.WriteLine($"{numberOne} + {numberTwo} = {add}");
            Console.WriteLine($"{numberOne} - {numberTwo} = {subtract}");
            Console.WriteLine($"{numberOne} x {numberTwo} = {multiply}");
            Console.WriteLine($"{numberOne} / {numberTwo} = {divide}");
            Console.WriteLine($"{numberOne} % {numberTwo} = {mod}");
        }
    }
}

