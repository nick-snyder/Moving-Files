using System;

namespace LabExam02_6
{
    class Program
    {
        static void Main(string[] args)
        {
            int x = 1, y = 0;

            while (x < 4)
            {
                Console.WriteLine($"{x} - Line 0 Lab Exam 1");
                Console.WriteLine($"{x} - Line 1 Lab Exam 1");
                Console.WriteLine($"{x} - Line 2 Lab Exam 1");
                Console.WriteLine();

                x++;

                while (y < 10)
                {
                    y++;

                    if (y > 3)
                    {
                        break;
                    }
                }
            }
        }
    }
}

