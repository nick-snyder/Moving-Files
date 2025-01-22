import java.util.Scanner;
/**
 * Program Description...
 *
 * @author Nicholas Snyder
 * @version 2 March 2021
 */
public class Menu {
    /**
     * Main method description...
     *
     * @param args main
     */
    public static void main(String[] args) {
        // Initializations
        String numbersString;
        String x;
        String y;
        String input;
        int space;
        int xInt;
        int yInt;
        double operation;
        // Declarations
        boolean bool = true;
        Scanner scanner = new Scanner(System.in);
        while (bool) {
            // Assignments and user input
            System.out.println("Please enter x and y:");
            numbersString = scanner.nextLine();
            space = numbersString.indexOf(' ');
            x = numbersString.substring(0, space);
            y = numbersString.substring(space + 1);
            xInt = Integer.parseInt(x);
            yInt = Integer.parseInt(y);
            System.out.println("Please enter a command:");
            input = scanner.nextLine();
            input = input.toUpperCase();
            // Outputs
            switch (input) {
                case "A" -> {
                    operation = xInt + yInt;
                    System.out.printf("%.0f\n", operation);
                }
                case "S" -> {
                    operation = xInt - yInt;
                    System.out.printf("%.0f\n", operation);
                }
                case "Q" -> {
                    System.out.println("Goodbye");
                    bool = false;
                }
                default -> System.out.println("Invalid command");
            }
        }
        scanner.close();
    }
}