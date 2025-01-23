import java.util.Scanner;

/**
 * Prog. desc.
 * 
 * @author Nicholas Snyder
 * @version 4 March 2021
 */

public class CheckByte {

    /**
     * Method desc.
     * 
     * @param args main
     */

    public static void main(String[] args) {

        int number;
        String cont;

        boolean bool = false;
        Scanner scnr = new Scanner(System.in);

        while (!bool) {

            System.out.println("Please enter a valid byte value:");
            number = scnr.nextInt();
            
            if ((number >= 0) && (number <= 255)) {

                System.out.println("Entered value " + number + " is a valid byte");
                
            } else {

                System.out.println("Entered value " + number + " is not a valid byte");

            }
            
            scnr.nextLine();
            System.out.println("Would you like to continue (y/n)");
            cont = scnr.nextLine();

            if (cont.equals("n")) {

                bool = true;
                
            }

            if (!cont.equals("y") && !cont.equals("n")) {

                System.out.println("INVALID RESPONSE");
                bool = true;

            }
        }
        
        System.out.println("Program ended.");
        
    }
}
