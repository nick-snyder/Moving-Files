using System;

namespace Three
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("number\t\tsquare\t\tcube");
            for (int num = 0; num < 11; num++)
            {
                Console.WriteLine($"{num}\t\t{num * num}\t\t{num * num * num}");
            }
        }
    }
}

