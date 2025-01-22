using System;

namespace Five
{
    class Program
    {
        static void Main(string[] args)
        {
            
            MakeNumPyramid();                                           // Pt. 1

            string[] colors = { "Black", "DarkBlue", "DarkGreen", "DarkCyan", "DarkRed", "DarkMagenta", 
                                "DarkYellow", "Gray", "DarkGray", "Blue", "Green", "Cyan", "Red", 
                                "Magenta", "Yellow", "White", "Black", "DarkBlue", "DarkGreen", 
                                "DarkCyan", "DarkRed", "DarkMagenta", "DarkYellow", "Gray", "DarkGray", 
                                "Blue", "Green", "Cyan", "Red", "Magenta", "Yellow", "White"};

            foreach(var item in colors)
            {
                Console.WriteLine(item.ToString());
            }
            Console.WriteLine("Pick a color from one of the above");
            string colorSelect = Console.ReadLine();
            Color(colorSelect);
            
            MakeNumPyramid();
            
            Console.ForegroundColor = ConsoleColor.White;               // Pt. 2

            Console.Write("Now enter a character: ");
            char charSelect = Convert.ToChar(Console.ReadLine());
            MakeCharPyramid(charSelect);                                // Pt. 3
        }
        private static void MakeNumPyramid()
        {
            int num = 1, rows = 4;
            char space = ' ';

            for (int i = 1; i < rows + 1; i++)
            {
                string tab = new string (space, (rows - i));

                switch (i)
                {
                    case 1:
                        Console.WriteLine(tab + num);
                        break;
                    case 2:
                        Console.Write(tab + num);
                        num++;
                        Console.WriteLine(" " + num);
                        break;
                    case 3:
                        Console.Write(tab + num);
                        num++;
                        Console.Write(" " + num);
                        num++;
                        Console.WriteLine(" " + num);
                        break;
                    case 4:
                        Console.Write(tab + num);
                        num++;
                        Console.Write(" " + num);
                        num++;
                        Console.Write(" " + num);
                        num++;
                        Console.WriteLine(" " + num);
                        break;
                    default:
                        break;
                }
                num++;
            }
        }
        private static void MakeCharPyramid(char charSelect)
        {                                                             //     \\
            for (int i = 1; i < 4 + 1; i++)
            {                                                       //         \\
                string tab = new string (' ', (4 - i));            //  Pyramid  \\
                                                                  //             \\ 
                switch (i)                                            
                {                       
                    case 1:
                                                        Console.WriteLine(tab + charSelect);
                        break;                               //                       \\
                    case 2:
                                                Console.WriteLine(tab + charSelect + " " + charSelect);
                        break;                            //                             \\
                    case 3:
                                    Console.WriteLine(tab + charSelect + " " + charSelect + " " + charSelect);
                        break;                         //                                   \\
                    case 4:
                        Console.WriteLine(tab + charSelect + " " + charSelect + " " + charSelect + " " + charSelect);
                        break;                      //                                         \\
                    default:
                        break;                    //      ^^^^ It looks like a pyramid ^^^^      \\
                }
            }
        }
        static void Color(string colorSelect)
        {
            switch (colorSelect)
            {
                case "Black":
                    Console.ForegroundColor = ConsoleColor.Black;
                    break;
                case "DarkBlue":
                    Console.ForegroundColor = ConsoleColor.DarkBlue;
                    break;
                case "DarkGreen":
                    Console.ForegroundColor = ConsoleColor.DarkGreen;
                    break;
                case "DarkCyan":
                    Console.ForegroundColor = ConsoleColor.DarkCyan;
                    break;
                case "DarkRed":
                    Console.ForegroundColor = ConsoleColor.DarkRed;
                    break;
                case "DarkMagenta":
                    Console.ForegroundColor = ConsoleColor.DarkMagenta;
                    break;
                case "DarkYellow":
                    Console.ForegroundColor = ConsoleColor.DarkYellow;
                    break;
                case "Gray":
                    Console.ForegroundColor = ConsoleColor.Gray;
                    break;
                case "DarkGray":
                    Console.ForegroundColor = ConsoleColor.DarkGray;
                    break;
                case "Blue":
                    Console.ForegroundColor = ConsoleColor.Blue;
                    break;
                case "Green":
                    Console.ForegroundColor = ConsoleColor.Green;
                    break;
                case "Cyan":
                    Console.ForegroundColor = ConsoleColor.Cyan;
                    break;
                case "Red":
                    Console.ForegroundColor = ConsoleColor.Red;
                    break;
                case "Magenta":
                    Console.ForegroundColor = ConsoleColor.Magenta;
                    break;
                case "Yellow":
                    Console.ForegroundColor = ConsoleColor.Yellow;
                    break;
                case "White":
                    Console.ForegroundColor = ConsoleColor.White;
                    break;
                default:
                    Console.ForegroundColor = ConsoleColor.White;
                    break;
            }
        }
    }           
}

