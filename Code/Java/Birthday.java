import java.util.Scanner;

/**
 * 
 * 
 * @author Nicholas Snyder
 * 
 */

public class Birthday {

    /**
     * 
     * 
     * @param args main
     */

    public static void main(String[] args) {
        
        // Variable declaration
        String year;
        String month;

        Scanner scnr = new Scanner(System.in);
        
        // User input
        System.out.println("What year were you born in? ");
        year = scnr.nextLine();

        System.out.println("hat month were you born in? ");
        month = scnr.nextLine();

        // Final print-out to the screen
        System.out.println(month + "/" + year);
        
        scnr.close();
    }
}
