using System;

namespace Exercise02_3
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
            int numberthree = Convert.ToInt32(Console.ReadLine());

            Console.Write("Enter the fourth number: ");
            int numberFour = Convert.ToInt32(Console.ReadLine());

            int average = (numberOne + numberTwo + numberthree + numberFour) / 4;
            Console.WriteLine($"The average of {numberOne}, {numberTwo}, {numberThree}, and {numberFour} is: {average}");
        }
    }
}

