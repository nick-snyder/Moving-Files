import java.util.Scanner;

/**
 * Payroll.java calculates the gross pay by multiplying hours worked
 * and hourly rate. A bonus of $500 is also added to the calculation
 *
 * @author Nicholas Snyder
 * @version 4 February 2021
 */

public class Payroll {

    /**
     * The main method first asks for your name and is stored as a
     * string with the variable "name". Main then asks how many hours
     * you have worked this week and stores the integer input to variable
     * "hoursWorked". Main then asks for your hourly rate and stores the double
     * input to variable "payRate". Main then calculates gross pay and
     * stores the value in the variable "grossPay". Main then outputs the
     * "name" variable to the console and ends the current line. Main
     * then outputs the "grossPay" variable to the console. The main
     * method is now finished.
     *
     * @param args name hoursWorked payRate
     */

    public static void main(String[] args) {

        final double BONUS = 500;

        String name;
        int hoursWorked;
        double payRate;
        double grossPay;

        Scanner keyboard;
        keyboard = new Scanner(System.in);

        // User input
        System.out.print("What is your name? ");
        name = keyboard.nextLine();

        // User input
        System.out.print("How many hours did you work this week? ");
        hoursWorked = keyboard.nextInt();

        // User input
        System.out.print("What is your hourly pay rate? ");
        payRate = keyboard.nextDouble();

        grossPay = hoursWorked * payRate + BONUS;

        // Prints to console
        System.out.println("Hello " + name);
        System.out.println("Your gross pay is $" + grossPay);
    }
}