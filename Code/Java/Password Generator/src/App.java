import java.util.Random;
import java.util.Scanner;

/**
 * Generates password
 * 
 * TODO: No duplicate characters
 *
 * @author Nick Snyder
 * @version 7 October 2021
 */
public class App 
{
    /**
     * Generates random string of letters, numbers, or symbols
     *
     * @param length The length of the requested password; int
     * @param hasLowercase Whether requested password has lowercase letters; boolean
     * @param hasUppercase Whether requested password has uppercase letters; boolean
     * @param hasNumbers Whether requested password has numbers; boolean
     * @param hasSymbols Whether requested password has symbols; boolean
     * @param hasUnique Whether requested password has unique characters; boolean
     * @return password; String
     */
    public static String generate(int length, boolean hasLowercase, boolean hasUppercase,
                          boolean hasNumbers, boolean hasSymbols, boolean hasUnique) 
    {
        // initialize Random object
        Random rng = new Random();

        // initialize stringBuilder of available characters
        StringBuilder availableCharacters = new StringBuilder();

        // if password requests lowercase letters
        if (hasLowercase) 
        {
            // add lowercase alphabet to available characters
            availableCharacters.append("abcdefghijklmnopqrstuvwxyz");
        }

        // if password requests uppercase letters
        if (hasUppercase) 
        {
            // add uppercase alphabet to available characters
            availableCharacters.append("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        }

        // if password requests numbers
        if (hasNumbers) 
        {
            // add base 10 numbers to available characters
            availableCharacters.append("0123456789");
        }

        // if password requests symbols
        if (hasSymbols) 
        {
            // add specified symbols to available characters
            availableCharacters.append("!@#$%^&*");
        }

        // initialize a variable containing the length of the available characters
        int totalAvailable = availableCharacters.length();

        // initialize password stringBuilder to be returned
        StringBuilder password = new StringBuilder();

        // for the length of the requested password
        for (int i = 0; i < length; i++) 
        {
            // create a randomized index of a character from the available characters
            int char1 = rng.nextInt(totalAvailable);

            // add randomized character to stringBuilder
            password.append(availableCharacters.charAt(char1));

            // if password requests unique characters
            if (hasUnique) 
            {
                // delete the character from the available characters
                //availableCharacters.deleteCharAt(char1);
                System.out.print("");
            }
        }

        // return completed string
        return password.toString();
    }

    /**
     * 
     * @param scanner
     * @return
     */
    public static boolean ask(Scanner scanner)
    {
        if (scanner.hasNextLine())
        {
            String input = scanner.nextLine();
            return input.isEmpty() ? true : input.equalsIgnoreCase("y");
        }
        return false;
    }

    /**
     * 
     * @param scanner
     * @param defaultLength
     * @return
     */
    public static int ask(Scanner scanner, int defaultLength)
    {
        if (scanner.hasNextLine())
        {
            String input = scanner.nextLine();
            return input.isEmpty() ? defaultLength : Integer.parseInt(input) > 0 ? Integer.parseInt(input) : defaultLength;
        }
        return defaultLength;
    }

    /**
     * Main method. Asks user about password specifics.
     * Prints output of called method to terminal
     *
     * @param args main method; String[]
     */
    public static void main(String[] args) 
    {
        // initialize Scanner object
        Scanner scanner = new Scanner(System.in);
        int defaultLength = 16;

        // ask user the requested length
        System.out.print("Length [default=" + defaultLength + "]: ");
        int length = ask(scanner, defaultLength);
        
        // asks user
        System.out.print("Has lowercase letters [y]/n: ");
        boolean hasLowercase = ask(scanner);        

        // asks user
        System.out.print("Has uppercase letters [y]/n: ");
        boolean hasUppercase = ask(scanner);
        
        // asks user
        System.out.print("Has numbers [y]/n: ");
        boolean hasNumbers = ask(scanner);

        // asks user
        System.out.print("Has symbols [y]/n: ");
        boolean hasSymbols = ask(scanner);

        // asks user
        System.out.print("Has unique (not implemented) [y]/n: ");
        boolean hasUnique = ask(scanner);
        
        // close scanner
        scanner.close();

        // print to terminal
        System.out.println("Passwords:");
        for (int i = 0; i < 10; i++)
        {
            System.out.println("\t" + generate(length, hasLowercase, hasUppercase, hasNumbers, hasSymbols, hasUnique));
        }
    }
}