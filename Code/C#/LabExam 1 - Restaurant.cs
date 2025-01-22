using System;

namespace Restaurant
{
    class Program
    {
        static void Main(string[] args)
        {
            int sel = -1;
            double subTotal = 0.0;

            while (true)
            {
                Console.ForegroundColor = ConsoleColor.Green;

                DisplayMenu();

                sel = GetSelection();

                if (sel == 5)
                {
                    break;
                }

                int qty = GetQuantity();

                Console.ForegroundColor = ConsoleColor.Cyan;

                subTotal = subTotal + ValidateSelection(sel, qty);

                Console.WriteLine($"  Your current subtotal is ${subTotal}");

                Console.ForegroundColor = ConsoleColor.Green;

                Console.Write("  Press any key to continue...");
                Console.ReadLine();

                Console.ForegroundColor = ConsoleColor.Green;
            }

            Console.ForegroundColor = ConsoleColor.Cyan;

            CalculateBill(sel, subTotal);

            Console.ForegroundColor = ConsoleColor.Green;

            Console.Write("  Press any key to continue...");
            Console.ReadLine();

            Console.ForegroundColor = ConsoleColor.White;
        }

        private static void DisplayMenu()
        {
            Console.WriteLine("  Cafe George Menu:\n        1  Prime Rib     - $13.99 per plate\n        2  Fried Chicken - $8.49 per plate\n        3  Baked Haddock - $9.99 per plate\n        4  Soda          - $1.99 per plate\n        5  Quit");
        }

        private static int GetSelection()
        {
            Console.Write("  Please make a selection: ");

            return Convert.ToInt32(Console.ReadLine());
        }

        private static int GetQuantity()
        {
            Console.Write("  Please enter a quantity: ");

            return Convert.ToInt32(Console.ReadLine());
        }

        private static double ValidateSelection(int sel, int qty)
        {
            string selString = "";
            double selPrice = 0.00;

            switch (sel)
            {
                case 1:
                    selString = "Prime Rib, @ $13.99 per plate";
                    selPrice = 13.99;
                    break;
                case 2:
                    selString = "Fried Chicken, @ $8.49 per plate";
                    selPrice = 8.49;
                    break;
                case 3:
                    selString = "Baked Haddock, @ $9.99 per plate";
                    selPrice = 9.99;
                    break;
                case 4:
                    selString = "Soda, @ $1.99 per each";
                    selPrice = 1.99;
                    break;
                default:
                    break;
            }

            Console.WriteLine($"  {qty} {selString} = ${Convert.ToDouble(qty) * selPrice}");

            double subTotal = Convert.ToDouble(qty) * selPrice;

            return subTotal;
        }

        private static void CalculateBill(int sel, double subTotal)
        {
            const double stateTax = 0.09;
            const double tipRate = 0.20;
           
            double tax = Math.Round(stateTax * subTotal, 2);
            double tip = Math.Round(tipRate * (subTotal + tax), 2);

            Console.WriteLine($"    Subtotal: ${subTotal}\n    Tax ({stateTax * 100}%): ${tax}\n   Tip ({tipRate * 100}%): ${tip}\n  Total Sale: ${subTotal + tax + tip}");
        }
    }
}