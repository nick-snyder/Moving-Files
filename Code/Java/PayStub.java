import java.util.Scanner;
/**
 * Program calculates net pay along with other
 * figures based on the input of some variables.
 *
 * @author Nicholas Snyder
 * @version 22 February 2021
 */
public class PayStub {
    /**
     * Main method first declares and initializes
     * variables. Then it assigns them to the user's
     * input. Next, more variables are assigned
     * through equations with other variables.
     * Variables are then printed to the screen in
     * a purposefully stylized configuration.
     *
     * @param args main
     */
    public static void main(String[] args) {
        // Variable declarations
        // In order in which they appear
        String name;
        String jobTitle;
        int anniversaryMonth;
        int anniversaryYear;
        int hoursWorked;
        int monthsWorked;
        double hourlyRate;
        double vacationHours;
        double grossPay;
        double retirementWithholding;
        double taxWithholding;
        double netPay;
        // Variable initializations
        final int CURRENT_MONTH = 2;
        final int CURRENT_YEAR = 2021;
        final int MONTHS_IN_YEAR = 12;
        final double VACATION_RATE = 8.25;
        final double RETIREMENT_RATE = 0.052;
        final double TAX_RATE = 0.28;
        Scanner scanner = new Scanner(System.in);
        // Variable assignments
        System.out.print("Enter your Full name: ");
        name = scanner.nextLine();
        System.out.print("Enter your Anniversary Mont(1-12): ");
        anniversaryMonth = scanner.nextInt();
        System.out.print("Enter your Anniversary Year: ");
        anniversaryYear = scanner.nextInt();
        System.out.print("Enter your hours worked this pay period(0-350): ");
        hoursWorked = scanner.nextInt();
        scanner.nextLine();    // Weird bug in java
        System.out.print("Enter your Job Title: ");
        jobTitle = scanner.nextLine();
        System.out.print("Enter your pay rate: ");
        hourlyRate = scanner.nextDouble();
        scanner.nextLine();    // Weird bug again
        scanner.close();
        // More assignments and calculations
        monthsWorked = (CURRENT_YEAR - anniversaryYear) * MONTHS_IN_YEAR + (CURRENT_MONTH - anniversaryMonth);
        vacationHours = VACATION_RATE * monthsWorked;
        grossPay = hoursWorked * hourlyRate;
        retirementWithholding = grossPay * RETIREMENT_RATE;
        taxWithholding = (grossPay - retirementWithholding) * TAX_RATE;
        netPay = grossPay - retirementWithholding - taxWithholding;
        // Output formatting
        System.out.print("""
                             ==========================================
                                   Gekko & Co.
                                       "$"
                                       ~~~        /   \\ `.
                                    /     \\  /
                                   / _ _ _ \\/
                             ------------------------------------------
                             """);
        System.out.println( "Pay Period:      " + CURRENT_MONTH + "/" + CURRENT_YEAR);
        System.out.println( "Name:            " + name);
        System.out.println( "Title:           " + jobTitle);
        System.out.println( "Anniversary:     " + anniversaryMonth + "/" + anniversaryYear);
        System.out.println( "Months worked:   " + monthsWorked + " months");
        System.out.print(   "Vacation hours: ");
        System.out.printf(  "%7.2f\n", vacationHours);
        System.out.print("""
                             ------------------------------------------
                             Gross pay:       $
                             """);
        System.out.printf(  "%7.2f\n", grossPay);
        System.out.print(   "Retirement:      $");
        System.out.printf(  "%7.2f\n", retirementWithholding);
        System.out.print(   "Tax:             $");
        System.out.printf(  "%7.2f\n", taxWithholding);
        System.out.println( "---------------------------");
        System.out.print(   "Net Pay:         $");
        System.out.printf(  "%7.2f\n", netPay);
        System.out.println( "==========================================");
    }
}