import java.util.Scanner;
/**
 *
 *
 * @author Nicholas Snyder
 * @version 8 March 2021
 */
public class Aquapodz1 {
    /**
     *
     *
     * @param args main
     */
    public static void main(String[] args) {
        String command;
        double numberOne;
        double numberTwo;
        double numberThree;
        int aFails = 0;
        int bFails = 0;
        int cFails = 0;
        boolean bool = true;
        Scanner scanner = new Scanner(System.in);
        while (bool) {
            System.out.println("Please enter a command:");
            command = scanner.nextLine();
            switch (command) {
                case "a", "b", "c" -> {
                    System.out.println("Enter number 1:");
                    numberOne = scanner.nextDouble();
                    System.out.println("Enter number 2:");
                    numberTwo = scanner.nextDouble();
                    System.out.println("Enter number 3:");
                    numberThree = scanner.nextDouble();
                    if (command.equals("a")) {
                        if ((numberOne < -6.0) || (numberOne > 12.3)) aFails++;
                        if ((numberTwo < -6.0) || (numberTwo > 12.3)) aFails++;
                        if ((numberThree < -6.0) || (numberThree > 12.3)) aFails++;
                    }
                    if (command.equals("b")) {
                        if ((numberOne < -6.0) || (numberOne > 12.3)) bFails++;
                        if ((numberTwo < -6.0) || (numberTwo > 12.3)) bFails++;
                        if ((numberThree < -6.0) || (numberThree > 12.3)) bFails++;
                    }
                    if (command.equals("c")) {
                        if ((numberOne < -6.0) || (numberOne > 12.3)) cFails++;
                        if ((numberTwo < -6.0) || (numberTwo > 12.3)) cFails++;
                        if ((numberThree < -6.0) || (numberThree > 12.3)) cFails++;
                    }
                    scanner.nextLine();
                }
                case "f" -> {
                    System.out.println("Azuview failures: " + aFails);
                    System.out.println("Bublon  failures: " + bFails);
                    System.out.println("Cryztal failures: " + cFails);
                }
                case "x" -> {
                    System.out.println("Program ended");
                    bool = false;
                }
                default -> System.out.println(command + " is not valid.");
            }
        }
        scanner.close();
    }
}