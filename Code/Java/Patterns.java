import java.util.Scanner;
/**
 *
 *
 * @author Nicholas Snyder
 * @version 9 March 2021
 */
public class Patterns {
    /**
     *
     *
     * @param args main
     */
    public static void main(String[] args) {
        String pattern;
        int number;
        Scanner scanner = new Scanner(System.in);
        do {
            System.out.println("Enter pattern:");
            pattern = scanner.nextLine();
        } while ((!pattern.equals("H")) && (!pattern.equals("V")) &&
                 (!pattern.equals("S")) && (!pattern.equals("T")) && (!pattern.equals("D")));
        System.out.println("Enter a positive integer between 1 and 10 inclusive:");
        number = scanner.nextInt();
        if (pattern.equals("H")) {
            for (int i = 0; i < number; i++) System.out.print("*");
        }
        if (pattern.equals("V")) {
            for (int i = 0; i < number; i++) System.out.println("*");
        }
        if (pattern.equals("S")) {
            for (int i = 0; i < number; i++) {
                for (int j = 0; j < number; j++) System.out.print("*");
                System.out.println();
            }
        }
        if (pattern.equals("T")) {
            for (int i = 0; i < number; i++) {
                for (int j = 0; j < i + 1; j++) System.out.print("*");
                System.out.println();
            }
        }
        if (pattern.equals("D")) {
            for (int i = 0; i < number; i++) {
                for (int j = 0; j < i; j++) System.out.print(" ");
                System.out.println("*");
            }
        }
        scanner.close();
    }
}