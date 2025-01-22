using System;

namespace LabExam02_5
{
    class Program
    {
        static void Main(string[] args)
        {
            int x = 0;

            while (x < 10)
            {
                x++;
                if (x == 4 || x == 7 || x == 9)
                {
                    x++;
                    Console.WriteLine($"Line {x} Lab Exam 1");
                    continue;
                }
                Console.WriteLine($"Line {x} Lab Exam 1");
            }
        }
    }
}

