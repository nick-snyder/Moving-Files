import java.util.Arrays;
import java.util.Scanner;
/**
 * 
 * 
 * @author Nicholas Snyder
 * @version 27 April 2021
 */

public class Endodoi {

    /**
     * 
     * 
     * @param pitsPerRow            int
     * @param numSeeds              int
     * @return                      int[][]
     */
    
    public static int[][] createNewPits(int pitsPerRow, int numSeeds) {
        int[][] array = new int[2][pitsPerRow];
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < pitsPerRow; j++) {
                array[i][j] = numSeeds;
            }
        }
        return array;
    }
    
    /**
     * 
     * 
     * @param playerPits            int[][]
     * @return                      char[][]
     */
    
    public static char[][] playerPitLabels(int[][] playerPits) {
        char letter = 'a';
        char[][] array = new char[playerPits.length][playerPits[0].length];
        for (int i = 0; i < playerPits.length; i++) {
            for (int j = 0; j < playerPits[i].length; j++) {
                array[i][j] = letter++;
            }
        }
        return array;
    }
    
    /**
     * 
     * 
     * @param gamePits              int[][]
     * @param storePlayer1          int
     * @param storePlayer2          int
     * @param selectedPit           char
     * @param indicatePlayerTurn    int
     * @return                      String
     */
    
    public static String drawBoard(int[][] gamePits, int storePlayer1, 
        int storePlayer2, char selectedPit, int indicatePlayerTurn) {
        String str = "";
        final String BORDER =  " +====++==++";
        str += BORDER;
        for (int line1 = 0; line1 < gamePits[1].length; line1++) {
            str += "----+";
        }
        if (indicatePlayerTurn == 1) {   
            str += "\n1|(";
            if (storePlayer1 == 0) {
                str += "  ";
            } else if (storePlayer1 > 9) {
                str += storePlayer1;
            } else {
                str += " " + storePlayer1;
            }
            str += ")||\\/||";
        } else {
            str += "\n1|(";
            if (storePlayer1 == 0) {
                str += "  ";
            } else if (storePlayer1 > 9) {
                str += storePlayer1;
            } else {
                str += " " + storePlayer1;
            }
            str += ")||  ||";
        }
        for (int i = 0; i < gamePits[1].length; i++) {   
            if (gamePits[0][i] == 0) {
                str += "(  )|";
            } else {
                str += "( " + gamePits[0][i] + ")|";
            }
        }

        if (indicatePlayerTurn == 1) {
            str += "\n | st ||/\\||";
        } else {
            str += "\n | st ||  ||";
        }
        for (int j = 0; j < gamePits[1].length; j++) {   
            if (playerPitLabels(gamePits)[0][j] == selectedPit) {
                str += "  * |";
            } else {
                if (indicatePlayerTurn == 2) {
                    str += "    |";
                } else {
                    str += "  " + playerPitLabels(gamePits)[0][j] + " |";
                }
            }
        }
        str += "\n" + BORDER;
        for (int line1 = 0; line1 < gamePits[1].length; line1++) {
            str += "----+";
        }
        if (indicatePlayerTurn == 2) {   
            str += "\n2|(";
            if (storePlayer2 == 0) {
                str += "  ";
            } else if (storePlayer2 > 9) {
                str += storePlayer2;
            } else {
                str += " " + storePlayer2;
            }
            str += ")||\\/||";
        } else {
            str += "\n2|(";
            if (storePlayer2 == 0) {
                str += "  ";
            } else if (storePlayer2 > 9) {
                str += storePlayer2;
            } else {
                str += " " + storePlayer2;
            }
            str += ")||  ||";
        }
        for (int i = 0; i < gamePits[1].length; i++) {   
            if (gamePits[1][i] == 0) {
                str += "(  )|";
            } else {
                str += "( " + gamePits[1][i] + ")|";
            }
        }
        if (indicatePlayerTurn == 2) {   
            str += "\n | st ||/\\||";
        } else {
            str += "\n | st ||  ||";
        }
        for (int j = 0; j < gamePits[1].length; j++) {   
            if (playerPitLabels(gamePits)[1][j] == selectedPit) {
                str += "  * |";
            } else {
                if (indicatePlayerTurn == 1) {
                    str += "    |";
                } else {
                    str += "  " + playerPitLabels(gamePits)[1][j] + " |";
                }
            }
        }
        str += "\n" + BORDER;
        for (int line1 = 0; line1 < gamePits[1].length; line1++) {
            str += "----+";
        }
        str += "\n";
        return str;        
    }

    /**
     *
     *
     * @param pitLabel              char
     * @param playerPits            int[][]
     * @return                      int[]
     */
    
    public static int[] pit2Coordinates(char pitLabel, int[][] playerPits) {
        int[] array = new int[2];
        char[][] cArray = playerPitLabels(playerPits);
        for (int i = 0; i < cArray.length; i++) {
            for (int j = 0; j < cArray[i].length; j++) {
                if (cArray[i][j] == pitLabel) {
                    array[0] = i;
                    array[1] = j;
                }
            }
        }
        return array;
    }
    
    /**
     *
     *
     * @param pit                   char
     * @param playerPits            int[][]
     * @return                      char
     */
    
    public static char getOpposingPit(char pit, int[][] playerPits) {
        char chr = 'a';
        char[][] cArray = playerPitLabels(playerPits);
        for (int i = 0; i < playerPits[0].length; i++) {
            if (pit == cArray[0][i]) {
                chr = cArray[1][i];
            }
            if (pit == cArray[1][i]) {
                chr = cArray[0][i];
            }
        }
        return chr;
    }
    
    /**
     *
     *
     * @param player                int
     * @param pit                   char
     * @param playerPits            int[][]
     * @return                      boolean
     */
    
    public static boolean isPitInPlayerRow(int player, char pit, int[][] playerPits) {
        for (int i = 0; i < playerPits[0].length; i++) {
            if (playerPitLabels(playerPits)[player - 1][i] == pit) {
                return true;
            }
        }
        return false;
    }
    
    /**
     *
     *
     * @param currentPit            char
     * @param playersPits           int[][]
     * @return                      char
     */
    
    public static char nextPit(char currentPit, int[][] playersPits) {
        final int LEFT_BOUND = 0;
        final int RIGHT_BOUND = playersPits[0].length - 1;
        String str = Arrays.toString(pit2Coordinates(currentPit, playersPits)).substring(4, 5);
        int whichColumn = Integer.parseInt(str);
        int whichRow = pit2Coordinates(currentPit, playersPits)[0];
        if (whichRow == 1) {
            if (whichColumn == RIGHT_BOUND) {
                currentPit -= playersPits[0].length;
            } else {
                currentPit++;
            }
        } else {
            if (whichColumn == LEFT_BOUND) {
                currentPit += playersPits[0].length;
            } else {
                currentPit--;
            }
        }
        return currentPit;
    }

    /**
     *
     *
     * @param pit                   char
     * @param playersPits           int[][]
     * @return                      int
     */

    public static int getPitSeedCount(char pit, int[][] playersPits) {
        int row = Integer.parseInt(Arrays.toString(pit2Coordinates(pit, playersPits)).substring(1, 2));
        int column = Integer.parseInt(Arrays.toString(pit2Coordinates(pit, playersPits)).substring(4, 5));
        return playersPits[row][column];
    }

    /**
     *
     *
     * @param pickPit               char
     * @param playerPits            int[][]
     * @return                      char
     */

    public static char singleSow(char pickPit, int[][] playerPits) {
        char chr = pickPit;
        int number = getPitSeedCount(pickPit, playerPits);
        String str = Arrays.toString(pit2Coordinates(chr, playerPits)).substring(4, 5);
        int column = Integer.parseInt(str);
        int row = pit2Coordinates(chr, playerPits)[0];
        playerPits[row][column] = 0;
        for (int i = 0; i < number; i++) {
            chr = nextPit(chr, playerPits);
            pit2Coordinates(chr, playerPits);
            str = Arrays.toString(pit2Coordinates(chr, playerPits)).substring(4, 5);
            column = Integer.parseInt(str);
            row = pit2Coordinates(chr, playerPits)[0];
            playerPits[row][column] += 1;
        }
        return chr;
    }

    /**
     *
     *
     * @param playersPits           int[][]
     * @param isPlayer1Turn         boolean
     * @return                      boolean
     */

    public static boolean checkEndGame(int[][] playersPits, boolean isPlayer1Turn) {
        int turn = 1;
        int zeros = 0;
        if (isPlayer1Turn) {
            turn = 0;
        }
        for (turn = turn; turn < 1; turn++) {
            for (int j = 0; j < playersPits[0].length; j++) {
                if (playersPits[turn][j] == 0) {
                    zeros++;
                }
            }
        }
        return zeros == playersPits[0].length;
    }

    /**
     *
     *
     * @param playerPits            int[][]
     * @return                      int
     */

    public static int totalSeedsOnBoard(int[][] playerPits) {
        int total = 0;
        for (int i = 0; i < playerPits.length; i++) {
            for (int j = 0; j < playerPits[0].length; j++) {
                total += playerPits[i][j];
            }
        }
        return total;
    }

    /**
     *
     *
     * @param playerPits            int[][]
     */

    public static void clearBoard(int[][] playerPits) {

        //playerPits = new int[2][playerPits[0].length];
        //System.out.println(Arrays.deepToString(playerPits));

        for (int i = 0; i < playerPits.length; i++) {
            for (int j = 0; j < playerPits[0].length; j++) {
                playerPits[i][j] = 0;
            }
        }
    }

    /**
     *
     *
     * @param playersPits           int[][]
     * @param player1Store          int
     * @param player2Store          int
     * @param isPlayer1Turn         boolean
     */

    public static void playGame(int[][] playersPits, int player1Store, int player2Store, boolean isPlayer1Turn) {

        Scanner scanner = new Scanner(System.in);
        char selectedPit = 0;
        int numSeeds;
        int lap;
        int turn;

        // Converts boolean to int
        if (isPlayer1Turn) {
            turn = 0;
        } else {
            turn = 1;
        }

        System.out.println("Starting game of Endodoi");

        while (totalSeedsOnBoard(playersPits) != 0) {

            //
            if (checkEndGame(playersPits, !isPlayer1Turn)) {

                System.out.println(drawBoard(playersPits, player1Store, player2Store, ' ', turn + 1));
                System.out.println("Player " + (turn + 1) + " can't move.");
                System.out.println("The remaining " + totalSeedsOnBoard(playersPits)
                        + " seeds go to Player " + (turn + 1));
                // remaining seeds go to opposite player
                if (turn == 0) {
                    System.out.println("The remaining " + totalSeedsOnBoard(playersPits)
                                     + " seeds go to Player 1");
                } else {
                    System.out.println("The remaining " + totalSeedsOnBoard(playersPits)
                                     + " seeds go to Player 2");
                }
                break;
            }

            System.out.println(drawBoard(playersPits, player1Store, player2Store, ' ', turn + 1));
            System.out.println("Player " + (turn + 1) + " choose a pit: ");
            selectedPit = scanner.next().charAt(0);

            // If '!' is pressed, game ends
            if (selectedPit == '!') {
                System.out.println("Game ended");
                break;
            }

            while (!isPitInPlayerRow(turn + 1, selectedPit, playersPits)) {

                System.out.println("Not a valid pit. Please pick again.");
                selectedPit = scanner.next().charAt(0);

                if (selectedPit == '!') {

                    System.out.println("Game ended");
                    break;
                }
            }

            selectedPit = singleSow(selectedPit, playersPits);
            System.out.println(drawBoard(playersPits, player1Store, player2Store, selectedPit, turn + 1));
            lap = 1;
            while (getPitSeedCount(selectedPit, playersPits) != 1) {

                System.out.println("Sowing ended in non-empty pit. Multi-lap " + lap++ + ". Resowing seeds...");

                selectedPit = singleSow(selectedPit, playersPits);

                //System.out.println(getPitSeedCount(selectedPit, playersPits));
                //                if (getPitSeedCount(selectedPit, playersPits) == 0) {
                //
                //                    break;
                //                }

                System.out.println(drawBoard(playersPits, player1Store, player2Store, selectedPit, turn + 1));
            }

            System.out.println("Player " + (turn + 1) + "'s turn ended.");

            if (getPitSeedCount(getOpposingPit(selectedPit, playersPits), playersPits) != 0) {

                numSeeds = getPitSeedCount(selectedPit, playersPits);
                String str = Arrays.toString(pit2Coordinates(selectedPit, playersPits)).substring(4, 5);
                int column = Integer.parseInt(str);
                int row = pit2Coordinates(selectedPit, playersPits)[0];
                playersPits[row][column] = 0;

                if (isPitInPlayerRow(turn + 1, selectedPit, playersPits)) {

                    numSeeds += getPitSeedCount(getOpposingPit(selectedPit, playersPits), playersPits);
                    str = Arrays.toString(pit2Coordinates(getOpposingPit(selectedPit, playersPits), 
                                                            playersPits)).substring(4, 5);
                    column = Integer.parseInt(str);
                    row = pit2Coordinates(getOpposingPit(selectedPit, playersPits), playersPits)[0];
                    playersPits[row][column] = 0;
                } else {
                    numSeeds -= 2;
                }
                System.out.println("Player " + (turn + 1) + " captured " + numSeeds + " seeds");
            } else {
                numSeeds = 0;
            }

            if (turn == 0) {
                player1Store += numSeeds;
                turn = 1;
            } else {
                player2Store += numSeeds;
                turn = 0;
            }
        }

        clearBoard(playersPits);
        //System.out.println(drawBoard(playersPits, player1Store, player2Store, ' ', -1));

        if (selectedPit != '!') {
            if (player1Store > player2Store) {
                System.out.println("Player 1 is the winner!");
            } else if (player1Store < player2Store) {
                System.out.println("Player 2 is the winner!");
            } else {
                System.out.println("It was a draw!");
            }
        }
        scanner.close();
        //while (sowing ended in non-empty pit) {       getSeedCount(selectedPit, playersPits) == 0
        //    establish counter                         int lap = 1
        //    print message                             Sowing ended in non-empty pit. Multi-lap {lap}. Resowing...
        //    reassign selected pit with singleSow      selectedPit = singleSow(selectedPit, playersPits);
        //    print updated board                       drawBoard(...)
        //reassess }
        //print turn is over                            Player {turn}'s turn ended
        //print summary                                 Player {turn} captured {numSeeds} seeds
    
        //while (sowing ended in non-empty pit) {       getSeedCount(selectedPit, playersPits) == 0
        //    establish counter                         int lap = 1
        //    print message                             Sowing ended in non-empty pit. Multi-lap {lap}. Resowing...
        //    reassign selected pit with singleSow      selectedPit = singleSow(selectedPit, playersPits);
        //    print updated board                       drawBoard(...)
        //reassess }
        //print turn is over                            Player {turn}'s turn ended
        //print summary                                 Player {turn} captured {numSeeds} seeds
    }


    /**
     * 
     * 
     * @param args                  String[]
     */

    // public static void main(String[] args) {
    //     int[][] gamePits = new int[2][3];
    //     StringBuilder stringBuilder = new StringBuilder();
    //     stringBuilder.append("----+".repeat(gamePits[1].length));   // MIMIR doesn't like .repeat method
    //     System.out.println(stringBuilder);
    // }
}