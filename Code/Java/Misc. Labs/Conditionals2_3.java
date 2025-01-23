import java.util.Scanner;
public class Conditionals2_3 {
    public static void main(String[] args) {
        String word;
        Scanner scanner = new Scanner(System.in);
        System.out.println("enter a word");
        word = scanner.nextLine();
        word = word.toLowerCase();
        if ( (word.charAt(0) == 'a') || (word.charAt(0) == 'e') || (word.charAt(0) == 'i') || (word.charAt(0) == 'o') || (word.charAt(0) == 'u') ) {
            System.out.println("Starts with a vowel");
        } else {
            System.out.println("Starts with a consonant");
        }
        scanner.close();
    }
}