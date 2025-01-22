import java.util.Scanner;

/**
 * Program tells user stats of a given number.
 * 
 * @author Nicholas Snyder
 * @version 23 February 2021
 */

public class NumberStats {

    /**
     * Main first initializes and declares variables 
     * then asks user to input an integer and assigns 
     * the value to a variable. Main then runs the 
     * integer through some conditional statements to 
     * then print to the console.
     * 
     * @param args main
     */

    public static void main(String[] args) {
        
        // Initialization
        int number;

        // Declaration
        Scanner scnr = new Scanner(System.in);

        // User input
        System.out.println("Enter an integer:");
        number = scnr.nextInt();

        // Shows what number was entered
        System.out.println("+ Number entered: \n" + number);

        // Conditionals with Checkstyle
        if (number % 2 == 0) {

            System.out.println("+ Number is even");

        } else {

            System.out.println("+ Number is odd");
        }
        
        // More conditionals with Checkstyle
        if (number > 50) {

            System.out.println("+ Number is greater than 50");

        } else if (number < 50) {

            System.out.println("+ Number is less than 50");
            
        } else {

            System.out.println("+ Number is equal to 50");
        }

        /*
        // Conditional statements w/o Checkstyle
        if (number % 2 == 0) System.out.println("+ Number is even");
        if (number % 2 != 0) System.out.println("+ Number is odd");

        // More conditional statements w/o Checkstyle
        if (number > 50) System.out.println("+ Number is greater than 50");
        if (number < 50) System.out.println("+ Number is less than 50");
        if (number == 50) System.out.println("+ Number is equal to 50");
        */

        // The End.
    }
}
