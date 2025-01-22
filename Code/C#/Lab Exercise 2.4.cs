using System;

namespace Exercise02_4
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Enter the first number: ");
            int numberOne = Convert.ToInt32(Console.ReadLine());
            
            Console.Write("Enter the second number: ");
            int numberTwo = Convert.ToInt32(Console.ReadLine());

            Console.Write("Enter the third number: ");
            int numberThree = Convert.ToInt32(Console.ReadLine());

            int equationOne = (numberOne + numberTwo) * numberThree;
            int equationTwo = numberOne * numberTwo + numberTwo * numberthree;

            Console.WriteLine($"Result of specified numbers: {numberOne}, {numberTwo}, and {numberThree}, (x+y)*z is: {equationOne} and x*y+y*z is {equationTwo}");
        }
    }
}

