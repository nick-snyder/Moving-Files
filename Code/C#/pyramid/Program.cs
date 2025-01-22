using System;

namespace Program
{
    class Program
    {
        private static int rows = 4;

        static void Main(string[] args)
        {
            Console.WriteLine("Default pyramid:");
            MakeNumPyramid();                                           // Pt. 1

            string[] colors = { "Black", "DarkBlue", "DarkGreen", "DarkCyan", 
                                "DarkRed", "DarkMagenta", "DarkYellow", "Gray", 
                                "DarkGray", "Blue", "Green", "Cyan", "Red", 
                                "Magenta", "Yellow", "White" };
            Console.WriteLine("\nAvailable colors:");
            foreach(var item in colors)
            {
                Console.WriteLine("    - " + item.ToString());
            }
            Console.Write("\nPick a color from one of the above: ");
            string colorSelect = Console.ReadLine();

            Color(colorSelect);
            MakeNumPyramid();
            
            Console.ForegroundColor = ConsoleColor.White;               // Pt. 2

            Console.Write("\nNow enter a character: ");
            string charSelect = Console.ReadLine();

            Color(colorSelect);
            MakeCharPyramid(charSelect);                                // Pt. 3

            Console.ForegroundColor = ConsoleColor.White;  
        }

        private static void MakeNumPyramid()
        {
            int num = 0;
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

        private static void MakeCharPyramid(string charSelect = "0")
        {                               
                                        
            for (int i = 1; i < rows + 1; i++)
            {                                                    
                string offset = new string (' ', (rows - i));
                
                switch (i)                                            
                {                       
                    case 1:
                        Console.WriteLine(offset + charSelect);
                        break;                       
                    case 2:
                        Console.WriteLine(offset + charSelect + " " + charSelect);
                        break;                       
                    case 3:
                        Console.WriteLine(offset + charSelect + " " + charSelect + " " + charSelect);
                        break;                        
                    case 4:
                        Console.WriteLine(offset + charSelect + " " + charSelect + " " + charSelect + " " + charSelect);
                        break;                     
                    default:
                        break;               
                }
            }
        }

        static void Color(string colorSelect)
        {
            colorSelect = colorSelect.ToLower();
            switch (colorSelect)
            {
                case "black":
                    Console.ForegroundColor = ConsoleColor.Black;
                    break;
                case "darkblue":
                    Console.ForegroundColor = ConsoleColor.DarkBlue;
                    break;
                case "darkgreen":
                    Console.ForegroundColor = ConsoleColor.DarkGreen;
                    break;
                case "darkcyan":
                    Console.ForegroundColor = ConsoleColor.DarkCyan;
                    break;
                case "darkred":
                    Console.ForegroundColor = ConsoleColor.DarkRed;
                    break;
                case "darkmagenta":
                    Console.ForegroundColor = ConsoleColor.DarkMagenta;
                    break;
                case "darkyellow":
                    Console.ForegroundColor = ConsoleColor.DarkYellow;
                    break;
                case "gray":
                    Console.ForegroundColor = ConsoleColor.Gray;
                    break;
                case "darkgray":
                    Console.ForegroundColor = ConsoleColor.DarkGray;
                    break;
                case "blue":
                    Console.ForegroundColor = ConsoleColor.Blue;
                    break;
                case "green":
                    Console.ForegroundColor = ConsoleColor.Green;
                    break;
                case "cyan":
                    Console.ForegroundColor = ConsoleColor.Cyan;
                    break;
                case "red":
                    Console.ForegroundColor = ConsoleColor.Red;
                    break;
                case "magenta":
                    Console.ForegroundColor = ConsoleColor.Magenta;
                    break;
                case "yellow":
                    Console.ForegroundColor = ConsoleColor.Yellow;
                    break;
                case "white":
                    Console.ForegroundColor = ConsoleColor.White;
                    break;
                default:
                    Console.ForegroundColor = ConsoleColor.White;
                    break;
            }
        }
    }           
}

