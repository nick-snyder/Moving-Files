using System;

namespace Exercise02_5
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Enter your age: ");
            int age = Convert.ToInt32(Console.ReadLine());
            
            if (age > 50)
            {
                Console.WriteLine($"You younger than {age}");
            }
            else
            {
                Console.WriteLine($"You look older than {50}");
            }
        }
    }
}

