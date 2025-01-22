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
        boolean bool = true;
        String cont;
        Scanner scanner = new Scanner(System.in);
        while (bool) {
            System.out.println("Please enter a valid byte value:");
            number = scanner.nextInt();
            if ((number >= 0) && (number <= 255)) {
                System.out.println("Entered value " + number + " is a valid byte");
            } else {
                System.out.println("Entered value " + number + " is not a valid byte");
            }
            scanner.nextLine();
            System.out.println("Would you like to continue (y/n)");
            cont = scanner.nextLine();
            if (cont.equals("n")) bool = false;
            if (!cont.equals("y") && !cont.equals("n")) {
                System.out.println("INVALID RESPONSE");
                bool = false;
            }
        }
        System.out.println("Program ended.");
        scanner.close();
    }
}