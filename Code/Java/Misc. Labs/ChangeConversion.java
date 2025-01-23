import java.util.Scanner;
/**
 * Convert  $0.99 to 3 quarters, 2 dimes, and 4 pennies
 *
 * @author Nicholas Snyder
 * @version 1.0
 */
public class ChangeConversion {
    /**
     * Does a thing
     *
     * @param args main
     */
    public static void main(String[] args) {
        double cents;
        int numQuarters = 0;
        int numDimes = 0;
        int numNickels = 0;
        int numPennies = 0;
        final double quarter = 0.25;
        final double dime = 0.10;
        final double nickel = 0.05;
        final double penny = 0.01;
        Scanner sc = new Scanner(System.in);
        System.out.println("How much money do you have?");
        cents = sc.nextDouble();
        while (cents >= quarter) {
            cents = cents - quarter;
            numQuarters = numQuarters + 1;
        }
        while (cents >= dime) {
            cents = cents - dime;
            numDimes = numDimes + 1;
        }
        while (cents >= nickel) {
            cents = cents - nickel;
            numNickels = numNickels + 1;
        }
        while (cents > 0) {     // Bug
            cents = cents - penny;
            numPennies = numPennies + 1;
        }
        System.out.print("You now have ");
        System.out.print(numQuarters + " quarters, ");
        System.out.print(numDimes + " dimes, ");
        System.out.print(numNickels + " nickels, and ");
        System.out.print(numPennies + " pennies.");
        sc.close();
    }
}