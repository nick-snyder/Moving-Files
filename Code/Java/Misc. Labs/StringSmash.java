import java.util.Scanner;

/**
 * 
 * 
 * @author Nicholas Snyder
 * @version 16 March 2021
 */

public class StringSmash {

    /**
     * 
     * 
     * @param args main
     */

    public static void main(String[] args) {

        // Variables
        String str1;
        String str2;
        String str3;

        Scanner scanner = null;
        try {
            scanner = new Scanner(System.in);

            System.out.println("Enter string:");
            str1 = scanner.nextLine();

            System.out.println("Enter string:");
            str2 = scanner.nextLine();

            System.out.println("Enter string:");
            str3 = scanner.nextLine();

            System.out.println(str1 + str2 + str3);
            // Done
        }
        finally {
            if (scanner != null)
                scanner.close();
        }
        
    }
}
