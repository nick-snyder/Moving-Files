import java.util.Scanner;
/**
 *
 *
 * @author Nicholas Snyder
 * @version 16 March 2021
 */
public class Waterfall {
    /**
     *
     *
     * @param args main
     */
    public static void main(String[] args) {
        int number;
        int x = 0;
        int forward = 0;
        int backward = 0;
        Scanner scanner = new Scanner(System.in);
        number = scanner.nextInt();
        for (int i = number; i > 0; i--) {
            for (int j = i; j > 0; j--) {
                if (x % 2 != 0) {
                    System.out.print("/");
                    forward++;
                } else {
                    System.out.print("\\");
                    backward++;
                }
            }
            x++;
            System.out.println();
        }
        System.out.println("\nTotal \\: " + backward);
        System.out.println("Total /: " + forward);
        scanner.close();
    }
}