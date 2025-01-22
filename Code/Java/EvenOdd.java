import java.util.Scanner;
/**
 *
 *
 * @author Nicholas Snyder
 * @version 16 March 2021
 */
public class EvenOdd {
    /**
     *
     *
     * @param args main
     */
    public static void main(String[] args) {
        int totalEven = 0;
        int totalOdd = 0;
        final String SENTINEL = ";";
        Scanner scanner = new Scanner(System.in);
        while (true) {
            String input = scanner.nextLine();
            if (input.equals(SENTINEL)) {
                break;
            } else {
                int number = Integer.parseInt(input);
                if (number % 2 == 0) {
                    totalEven++;
                } else {
                    totalOdd++;
                }
            }
        }
        if (totalEven > totalOdd) {
            System.out.println("E");
        } else if (totalEven < totalOdd) {
            System.out.println("O");
        } else {
            System.out.println("=");
        }
        scanner.close();
    }
}