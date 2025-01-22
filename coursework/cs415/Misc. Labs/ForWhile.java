import java.util.Scanner;

/**
 * 
 * 
 * @author Nicholas Snyder
 * @version 23 March 2021
 */

public class ForWhile {

    /**
     * 
     * 
     * @param args main
     */

    public static void main(String[] args) {
        
        int size;
        double sum = 0;
        int arrayLength = 0;
        double average;
        double gpaConversion;

        Scanner scanner = new Scanner(System.in);

        System.out.println("GPA Calculator");
        System.out.print("Enter total classes: ");
        size = scanner.nextInt();

        double[] arr = new double[size];

        for (int i = 1; i <= size; i++) {

            System.out.print("Enter grade for class " + i + ": ");

            while (!scanner.hasNextDouble()) {

                scanner.next();
                System.out.println("Percentage grades only please!");
                System.out.print("Enter grade for class " + i + ": ");
                scanner.nextLine();

                if (scanner.hasNextDouble()) {

                    break;
                }
            }

            arr[i - 1] = scanner.nextDouble();

            sum += arr[i - 1];
            arrayLength++;      
        }

        average = sum / arrayLength;
        gpaConversion = average / 20 - 1;

        if (gpaConversion < 0) {

            gpaConversion = 0;
        }

        System.out.printf("Your GPA: %.2f\n", gpaConversion);

        scanner.close();
    }
}
