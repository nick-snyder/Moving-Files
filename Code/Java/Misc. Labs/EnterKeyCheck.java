import java.util.Scanner;

public class EnterKeyCheck {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Press Enter to continue...");
        
        // Check for Enter key press
        if (scanner.hasNextLine()) {
            String userInput = scanner.nextLine();
            if (userInput.isEmpty()) {
                System.out.println("Enter key was pressed.");
            } else {
                System.out.println("Enter key was not pressed. You entered: " + userInput);
            }
        }
        
        scanner.close();
    }
} 
