import java.util.Scanner;
/**
 * Program desc.
 *
 * @author Nicholas Snyder
 * @version 1 March 2021
 */
public class EscapeRoom {
    /**
     * Method desc.
     *
     * @param args main
     */
    public static void main(String[] args) {
        // Initialization
        String doorOrStairs;
        int buttonPressed;
        int cookiesAte;
        int numRemainingCookies;
        double weightGuess;
        // Declaration
        final double WEIGHT_PER_COOKIE = 1.5;
        Scanner scanner = new Scanner(System.in);
        System.out.println("You are in a room with a door and stairs. Which way will you go?");
        doorOrStairs = scanner.nextLine();
        if (doorOrStairs.equals("door")) {
            System.out.println("There are 2 buttons on the door. Which do you press?");
            buttonPressed = scanner.nextInt();
            if (buttonPressed == 1) {
                System.out.println("A trap door opens underneath your feet and you fall. GAME OVER");
            } else if (buttonPressed == 2) {
                System.out.println("The door opens. You're free. YOU WIN!");
            } else {
                System.out.println("You hurt your finger pressing a button that doesn't exist. GAME OVER");
            }
        } else if (doorOrStairs.equals("stairs")) {
            System.out.println("There are cookies on a plate. How many do you eat?");
            cookiesAte = scanner.nextInt();
            if (cookiesAte < 2) {
                System.out.println("Your friends eat all the rest. You get too hungry and have to quit. GAME OVER");
            } else if (cookiesAte > 5) {
                System.out.println("You get a stomach ache and can't search any more. GAME OVER");
            } else {
                System.out.print("You notice a secret keypad under the cookie plate. Enter the ");
                System.out.println("weight of the remaining cookies in ounces, if each one weighs 1.5 ounces.");
                weightGuess = scanner.nextDouble();
                numRemainingCookies = 10 - cookiesAte;
                if (weightGuess == (numRemainingCookies * WEIGHT_PER_COOKIE)) {
                    System.out.println("A secret door opens for you to exit. YOU WIN!");
                } else {
                    System.out.println("Incorrect. GAME OVER");
                }
            }
        } else {
            System.out.println("That's not a valid direction. You trip and fall. GAME OVER");
        }
        scanner.close();
    }
}