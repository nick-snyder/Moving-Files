import java.util.Scanner;

/**
 * Program calculates the interest earned, total 
 * investment, and average interest after twelve months 
 * after entering the principle and interest rate.
 * 
 * @author Nicholas Snyder
 * @version 11 February 2021
 */

public class Interest {
    
    /**
     * The main method starts first by initializing the 
     * variables that will be used in the program. Main 
     * then creates a Scanner input and proceeds to ask 
     * the user to assign the principle and interest rate.
     * Interest earned is calculated by multiplying the 
     * principle and the interest rate. Investment value 
     * is calculated by adding interest earned by the 
     * principle. Average interest is calculated by 
     * dividing interest earned by twelve. Lastly, 
     * interest earned, investment value, and average 
     * interest are printed to the console.
     * 
     * @param args main
     */

    public static void main(String[] args) {
    
        // Initialize variables
        double principle;
        double interestRate;
        double interestEarned;
        double investmentValue;
        double averageInterest;
        final double MONTH_IN_A_YEAR = 12;
        Scanner sc;

        sc = new Scanner(System.in);

        System.out.println("Enter the principal value"); // Wrong spelling???
        principle       = sc.nextDouble();               // Dollars

        System.out.println("Enter the interest rate");
        interestRate    = sc.nextDouble();               // Percent

        interestEarned  = principle * interestRate;
        investmentValue = principle + (principle * interestRate);
        averageInterest = interestEarned / MONTH_IN_A_YEAR;

        // Prints to console
        System.out.print("The interest earned is $");
        System.out.printf("%.2f", interestEarned);
        System.out.print("\nThe value of the investment after one year is $");
        System.out.printf("%.2f", investmentValue);
        System.out.print("\nThe average interest is $");
        System.out.printf("%.2f", averageInterest);
    }
}