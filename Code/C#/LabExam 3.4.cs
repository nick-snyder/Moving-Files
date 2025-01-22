using System;

namespace Four
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Welcome to the body mass index (BMI) calculator");
            Console.Write("Enter your weight in pounds: ");
            double weight = Convert.ToDouble(Console.ReadLine());

            Console.Write("Enter your height in inches: ");
            double height = Convert.ToDouble(Console.ReadLine());

            double bmi = weight * 703 / Math.Pow(height, 2);
            bmi = Math.Round(bmi, 1);

            Console.WriteLine($"Your BMI is {bmi}");

            Console.Write(@"
BMI VALUES
Underweight: less than 18.5
Normal: between 18.5 and 24.9
Overweight: between 25 and 29.9
Obese: 30 or greater");
        }
    }
}

