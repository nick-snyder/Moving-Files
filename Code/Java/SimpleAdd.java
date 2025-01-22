import java.util.Scanner;
/**
 *
 *
 * @author Nicholas Snyder
 * @version 1.0
 */
public class SimpleAdd {
    /**
     *
     *
     * @param args String[]
     */
    public static void main(String[] args) {
        // initialize variables
        int a;
        int b;
        int sum;
        // initialize Scanner
        Scanner scanner = new Scanner(System.in);
        a = scanner.nextInt();
        b = scanner.nextInt();
        // Operation
        sum = a + b;
        // Prints to screen
        System.out.println(sum);
        scanner.close();
    }
}