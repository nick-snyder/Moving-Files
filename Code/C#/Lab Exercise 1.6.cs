using System;

namespace Exercise01_6
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Input the first number to multiply: ");
            int numberOne = Convert.ToInt32(Console.ReadLine());
            
            Console.Write("Input the second number to multiply: ");
            int numberTwo = Convert.ToInt32(Console.ReadLine());
            
            Console.Write("Input the third number to multiply: ");
            int numberThree = Convert.ToInt32(Console. ReadLine());
            
            int solution = numberOne * numberTwo * numberThree;

            Console.WriteLine($"{numberOne} x {numberTwo} x {numberThree} = {solution}");
        }
    }
}

