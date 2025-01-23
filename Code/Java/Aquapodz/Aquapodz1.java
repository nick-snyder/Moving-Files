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

        Scanner scnr = new Scanner(System.in);

        while (true) {

            System.out.println("Please enter a command:");
            command = scnr.nextLine();

            if ((command.equals("a")) || (command.equals("b")) || (command.equals("c"))) {

                System.out.println("Enter number 1:");
                numberOne = scnr.nextDouble();

                System.out.println("Enter number 2:");
                numberTwo = scnr.nextDouble();

                System.out.println("Enter number 3:");
                numberThree = scnr.nextDouble();

                if (command.equals("a")) {
                    
                    if ((numberOne < -6.0) || (numberOne > 12.3)) {

                        aFails++;
                    }
    
                    if ((numberTwo < -6.0) || (numberTwo > 12.3)) {
    
                        aFails++;
                    }
    
                    if ((numberThree < -6.0) || (numberThree > 12.3)) {
    
                        aFails++;
                    }
                }

                if (command.equals("b")) {

                    if ((numberOne < -6.0) || (numberOne > 12.3)) {

                        bFails++;
                    }
    
                    if ((numberTwo < -6.0) || (numberTwo > 12.3)) {
    
                        bFails++;
                    }
    
                    if ((numberThree < -6.0) || (numberThree > 12.3)) {
    
                        bFails++;
                    }
                } 

                if (command.equals("c")) {
                    
                    if ((numberOne < -6.0) || (numberOne > 12.3)) {

                        cFails++;
                    }
    
                    if ((numberTwo < -6.0) || (numberTwo > 12.3)) {
    
                        cFails++;
                    }
    
                    if ((numberThree < -6.0) || (numberThree > 12.3)) {
    
                        cFails++;
                    }
                }

                scnr.nextLine();
            } else if (command.equals("f")) {

                System.out.println("Azuview failures: " + aFails);
                System.out.println("Bublon  failures: " + bFails);
                System.out.println("Cryztal failures: " + cFails);
            
            } else if (command.equals("x")) {
                
                System.out.println("Program ended");
                break;

            } else {

                System.out.println(command + " is not valid.");
            }
        }
    }
}
