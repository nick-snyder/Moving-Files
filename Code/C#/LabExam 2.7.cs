using System;

namespace LabExam02_7
{
    class Program
    {
        static void Main(string[] args)
        {
            int gradeSum = 0;
            string gradeLetter = "";

            Console.Write("How many grades do you wisk to enter: ");
            int num = Convert.ToInt32(Console.ReadLine());

            for (int i = 0; i < num; i++)
            {
                Console.Write($"What is grade number {i + 1}? ");
                int grade = Convert.ToInt32(Console.ReadLine());

                if (grade >= 90)
                {
                    gradeLetter = "A";
                }
                else if (grade >= 80)
                {
                    gradeLetter = "B";
                }
                else if (grade >= 70)
                {
                    gradeLetter = "C";
                }
                else if (grade >= 60)
                {
                    gradeLetter = "D";
                }
                else
                {
                    gradeLetter = "F";
                }

                Console.WriteLine($"Grade is {gradeLetter}");

                gradeSum = gradeSum + grade;
            }

            int average = gradeSum / num;

            Console.WriteLine($"Your average grade of {num} assignments is {average}");
        }        
    }
}

