import java.util.Scanner;

/**
 *
 *
 * @author Nicholas Snyder
 * @version April 12 2021
 */

public class PhraseGame {

    /**
     * 
     *
     * @param args main
     */

    public static void main(String[] args) {

        /*
        int totalGuesses;
        int incorrectGuesses;

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter number of guesses allowed between 1 and 11");
        totalGuesses = scanner.nextInt();

        System.out.println("Enter number of incorrect guesses");
        incorrectGuesses = scanner.nextInt();

        System.out.println(drawScoreboard(totalGuesses, incorrectGuesses));

        scanner.close();
        */

        System.out.println(displayGuessedLetters("Civilization"));
        //System.out.println(displaySecretPhrase("Can't stop the FEELING","caf"));

        // Change these two
        /*
        String secretPhrase = "Cat";
        int totalGuesses = 2;

        secretPhrase = secretPhrase.toLowerCase();

        playGame(secretPhrase, totalGuesses);
        */
    }

    /**
     * 
     * 
     * @param totalGuesses      int
     * @param incorrectGuesses  int
     * @return                  String
     */

    public static String drawScoreboard(int totalGuesses, int incorrectGuesses) {

        String finalResult = "+";

        for (int line1 = 0; line1 < totalGuesses; line1++) {
            
            finalResult += "-----+";

        }

        finalResult += "\n|";

        for (int line2 = 0; line2 < incorrectGuesses; line2++) {
                
            finalResult += "\\\\ //|";

        }

        finalResult = empty(totalGuesses, incorrectGuesses, finalResult);

        finalResult += "\n|";

        for (int line3 = 0; line3 < incorrectGuesses; line3++) {

            finalResult += " \\V/ |";

        }

        finalResult = empty(totalGuesses, incorrectGuesses, finalResult);

        finalResult += "\n|";

        for (int line4 = 0; line4 < incorrectGuesses; line4++) {

            finalResult += " /.\\ |";

        }

        finalResult = empty(totalGuesses, incorrectGuesses, finalResult);

        finalResult += "\n|";

        for (int line5 = 0; line5 < incorrectGuesses; line5++) {

            finalResult += "// \\\\|";

        }

        finalResult = empty(totalGuesses, incorrectGuesses, finalResult);

        finalResult += "\n";

        for (int line5 = 0; line5 < totalGuesses; line5++) {
            
            finalResult += "+-----";

        }

        finalResult += "+";

        return finalResult;

    }

    /**
     * 
     * 
     * @param totalGuesses      int
     * @param incorrectGuesses  int
     * @param finalResult       String
     * @return                  String
     */

    public static String empty(int totalGuesses, int incorrectGuesses, String finalResult) {
        
        if (totalGuesses > incorrectGuesses) {
            
            for (int i = incorrectGuesses; i < totalGuesses; i++) {
                
                finalResult += "     |";

            }
        }

        return finalResult;
    }

    /**
     * 
     * @param letters           String
     * @return                  String
     */

    public static String displayGuessedLetters(String letters) {

        String newLetters = "";
        
        //newLetters += letters.substring(0, 1);

        for (int i = 0; i < letters.length(); i++) {

            if (i > 0) {
                
                newLetters += ", ";
            }

            newLetters += letters.substring(i, i + 1);    
        }
        //newLetters = newLetters.replace(oldChar, newChar)

        return newLetters;
    }

    /**
     * 
     * @param secretPhrase      String
     * @param guessedLetters    String
     * @return                  String
     */

    public static String displaySecretPhrase(String secretPhrase, String guessedLetters) {
     
        char[] secretPhraseLetters = new char[secretPhrase.length()];
        char[] letters = new char[guessedLetters.length()];

        //secretPhrase = secretPhrase.toLowerCase();
        
        int j;

        String newPhrase = "";

        //letters[j] = Character.toUpperCase(letters[j]);

        for (int i = 0; i < secretPhraseLetters.length; i++) {
            
            secretPhraseLetters[i] = secretPhrase.charAt(i);
        }

        for (int i = 0; i < letters.length; i++) {
            
            letters[i] = guessedLetters.charAt(i);
        }

        for (int i = 0; i < secretPhraseLetters.length; i++) {

            char chr = secretPhraseLetters[i];

            
            for (j = 0; j < letters.length; j++) {
                
                if (letters[j] == ' ') {

                    newPhrase += " ";
                }

                if (letters[j] == chr) {

                    newPhrase += letters[j];

                    break;
                }
                if (Character.toUpperCase(letters[j]) == chr) {

                    newPhrase += Character.toUpperCase(letters[j]);

                    break;
                }
            }

            

            if (j == letters.length) {

                newPhrase += "-";
            } 
            
            
        }

        return newPhrase;
    }

    /**
     * 
     * @param secretPhrase      String
     * @param totalGuesses      int
     */

    public static void playGame(String secretPhrase, int totalGuesses) {
        
        Scanner scanner = new Scanner(System.in);

        String dashedWord = "";
        String guessedLetters = " ";
        String letter = "";
        String alphabet = "abcdefghijklmnopqrstuvwxyz";

        int incorrectGuesses = 0;

        while (totalGuesses > incorrectGuesses) {

            System.out.println(drawScoreboard(totalGuesses, incorrectGuesses));

            dashedWord = displaySecretPhrase(secretPhrase, guessedLetters);
            
            System.out.println("Secret Phrase: " + dashedWord);
            System.out.println("Guessed Letters:" + displayGuessedLetters(guessedLetters));
            System.out.println("Enter a letter to guess or \"!\" to end the game");

            letter = scanner.next();
            
            letter = letter.toLowerCase();

            //System.out.println("ZZZZZZZZZZ");
            if (letter.contains(alphabet)) {
                //System.out.println("LLLLLLL");
                if (guessedLetters.contains(letter)) {
                
                    System.out.println("You already guessed " + letter);
    
                } else {
                    
                    if (displaySecretPhrase(secretPhrase, guessedLetters).equals(dashedWord)) {
                        System.out.println("GGGGGGGG");
                        //continue;

                    } else {

                        System.out.println("No, " + letter + " is not in the phrase\n");
                        incorrectGuesses++;
                    }
                }

            } else if (letter.equals("!")) {

                break;

            } else {

                System.out.println("Not a valid guess!");

            }
            //System.out.println("PPPPPP");
            //guessedLetters += letter;
        }

        System.out.println(drawScoreboard(totalGuesses, incorrectGuesses));

        String wordBlock = "\n=======================================\n"
                        +   "No more guesses left. Game over!\n"
                        +   "The phrase was \"" + secretPhrase + "\"\n"
                        +   "=======================================";

        System.out.println(wordBlock);

        scanner.close();
    }
}
