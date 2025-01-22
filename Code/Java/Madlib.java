import java.util.Scanner;
/**
 * Program is a madlib game that lets the user input
 * nouns and adjectives to use in a phrase.
 *
 * @author Nicholas Snyder
 * @version 18 February 2021
 */
public class Madlib {
    /**
     * The main method first declares and initializes 
     * variables to be used in the program. Next the 
     * program asks the user to enter two nouns and 
     * two adjectives to be assigned to the 
     * corresponding variable. Then the nouns and 
     * adjectives are added to the correct line of 
     * text by combining them with a pre-existing 
     * string. Lastly, each line is printed to the 
     * screen. This is done by printing lineOne and 
     * lineTwo with the same command and separating 
     * them by a backslash n. The same is done with 
     * the other two lines to end the program.
     *
     * @param args main
     */
    public static void main(String[] args) {
        // Variable declaration
        String adjectiveOne;
        String adjectiveTwo;
        String nounOne;
        String nounTwo;
        // Variable initialization
        Scanner scanner = new Scanner(System.in);
        String lineOne = "Roses are ";
        String lineTwo = " are blue";
        String lineThree = " is ";
        String lineFour = "And so are you!";
        // Variable assignments
        System.out.print("Enter an adjective: ");
        adjectiveOne = scanner.nextLine();
        System.out.print("Enter a noun: ");
        nounOne = scanner.nextLine();
        System.out.print("Enter a noun: ");
        nounTwo = scanner.nextLine();
        System.out.print("Enter an adjective: ");
        adjectiveTwo = scanner.nextLine();
        // String concatenation
        lineOne = lineOne + adjectiveOne;
        lineTwo = nounOne + lineTwo;
        lineThree = nounTwo + lineThree + adjectiveTwo;
        // Line 4 stays the same
        // Output to console
        System.out.println(lineOne + "\n" + lineTwo);
        System.out.println(lineThree + "\n" + lineFour);
        scanner.close();
    }
}