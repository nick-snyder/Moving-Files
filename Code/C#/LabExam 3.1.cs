using System;

namespace One
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Please enter an integer: ");
            int inti = Convert.ToInt32(Console.ReadLine());

            Console.Write("Please enter a short integer: ");
            short short1 = Convert.ToInt16(Console.ReadLine());

            Console.Write("Please enter a long integer: ");
            long long1 = Convert.ToInt64(Console.ReadLine());

            Console.Write("Please enter a byte: ");
            byte bytel = Convert.ToByte(Console.ReadLine());

            Console.Write("Please enter a float: ");
            float flost1 = Convert.Tosingle(Console.ReadLine());

            Console.Write("Please enter a double: ");
            double double1 = Convert.ToDouble(Console.Readline());

            Console.Write("Please enter a decimal: ");
            decimal decimal1 = Convert.ToDecimal(Console.ReadLine());

            Console.Write("Please enter a character: ");
            char char1 = Convert.ToChar(Console.ReadLine());

            Console.Write("Please enter a boolean: ");
            bool bool1 = Convert.ToBoolean(Console.ReadLine());

            Console.Write("Please enter a string: ");
            string string1 = Console.ReadLine();

            Console.WriteLine($"1) The int is: {int1}\n2) The short is: {short1}");
            Console.WriteLine($"3) The long is: {long1}\n4) The byte is: {byte1}");
            Console.WriteLine($"5) The float is: {float1}\n6) The double is: {double1}");
            Console.WriteLine($"7) The decimal is: {decimal1}\n8) The char is: {char1}");
            Console.WriteLine($"7) The decimal is: {decimal1}\n8) The char is: {char1}");
            Console.WriteLine($"9) The bool is: {bool1}\n10) The string is: {string1}");
        }
    }
}

