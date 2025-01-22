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
        String str = "";
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter string:");
        str += scanner.nextLine();
        System.out.println("Enter string:");
        str += scanner.nextLine();
        System.out.println("Enter string:");
        str += scanner.nextLine();
        System.out.println(str);
        scanner.close();
    }
}