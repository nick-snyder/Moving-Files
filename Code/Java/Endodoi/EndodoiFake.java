import java.util.Scanner;
/**
 * Plays the game Endodoi.
 *
 * @author cgesen
 * @version 4/15/2019
 */

public class EndodoiFake {

    /**
     * Draws the endodoi board.
     * @param pits int[][]
     * @param storePlayer1 int
     * @param storePlayer2 int
     * @param selectedPit char
     * @param indicatePlayerTurn int
     */
    public static void drawBoard(int[][] pits, int storePlayer1, int storePlayer2, char selectedPit,
                                 int indicatePlayerTurn) {
        templateBorder(pits);
        playerPits(pits, 1, storePlayer1, indicatePlayerTurn);
        playerLetters(pits, playerPitLabels(pits), 0, indicatePlayerTurn, selectedPit);
        templateBorder(pits);
        playerPits(pits, 2, storePlayer2, indicatePlayerTurn);
        playerLetters(pits, playerPitLabels(pits), 1, indicatePlayerTurn, selectedPit);
        templateBorder(pits);
    }

    /**
     * Sets up the the starting pits array.
     *
     * @param pitsPerRow int
     * @param numSeeds int
     * @return pits int[][]
     */
    public static int[][] createNewPits(int pitsPerRow, int numSeeds) {
        int[][] pits = new int[2][pitsPerRow];
        for (int i = 0; i < pits.length; i++) {
            for (int j = 0; j < pits[0].length; j++) {
                pits[i][j] = numSeeds;
            }
        }
        return pits;
    }

    /**
     * Sets up the pitLabels array.
     *
     * @param playerPits int[][]
     * @return pitLabels char[][]
     */
    public static char[][] playerPitLabels(int[][] playerPits) {
        char[][] pitLabels = new char[playerPits.length][playerPits[0].length];
        char letters = 'a';
        for (int i = 0; i < pitLabels.length; i++) {
            for (int j = 0; j < pitLabels[0].length; j++) {
                pitLabels[i][j] = letters;
                letters++;
            }
        }
        return pitLabels;
    }

    /**
     * Draws the board's border.
     *
     * @param pits int[][]
     */
    public static void templateBorder(int[][] pits) {
        System.out.print(" +====++==++");
        for (int i = 0; i < pits[0].length; i++) {
            System.out.print("----+");
        }
        System.out.println();
    }

    /**
     * Fills the pits with the number of seeds.
     *
     * @param pits int[][]
     * @param player int
     * @param storePlayer int
     * @param indicatePlayerTurn int
     */
    public static void playerPits(int[][] pits, int player, int storePlayer, int indicatePlayerTurn) {
        if (storePlayer >= 10) {
            System.out.print(player + "|(" + storePlayer + ")");
        } else if (storePlayer > 0) {
            System.out.print(player + "|( " + storePlayer + ")");
        } else {
            System.out.print(player + "|(  )");
        }
        if (indicatePlayerTurn == player) {
            System.out.print("||\\/||");
        } else {
            System.out.print("||  ||");
        }
        for (int i = 0; i < pits[player - 1].length; i++) {
            if (pits[player - 1][i] >= 10) {
                System.out.print("(" + pits[player - 1][i] + ")|");
            } else if (pits[player - 1][i] > 0) {
                System.out.print("( " + pits[player - 1][i] + ")|");
            } else {
                System.out.print("(  )|");
            }
        }
        System.out.println();
    }

    /**
     * Labels the pits.
     *
     * @param pits int[][]
     * @param letters char[][]
     * @param player int
     * @param indicatePlayerTurn int
     * @param selectedPit char
     */
    public static void playerLetters(int[][] pits, char[][] letters, int player, int indicatePlayerTurn,
                                     char selectedPit) {
        if (indicatePlayerTurn == player + 1) {
            System.out.print(" | st ||/\\||");
            for (int j = 0; j < pits[0].length; j++) {
                if (selectedPit == letters[player][j]) {
                    System.out.print("  * |");
                } else {
                    System.out.print("  " + letters[player][j] + " |");
                }
            }
        } else if (indicatePlayerTurn == -1) {
            System.out.print(" | st ||  ||");
            for (int j = 0; j < pits[0].length; j++) {
                if (selectedPit == letters[player][j]) {
                    System.out.print("  * |");
                } else {
                    System.out.print("  " + letters[player][j] + " |");
                }
            }
        } else {
            System.out.print(" | st ||  ||");
            for (int j = 0; j < pits[0].length; j++) {
                if (selectedPit == letters[player][j]) {
                    System.out.print("  * |");
                } else {
                    System.out.print("    |");
                }
            }
        }
        System.out.println();
    }

    /**
     * Gives the coordinates of a pit within the playerPits array.
     *
     * @param pitLabel char
     * @param playerPits int[][]
     * @return int[]
     */
    public static int[] pit2Coordinates(char pitLabel, int[][] playerPits) {
        int[] coordinates = new int[2];
        char[][] playerPitLabels = playerPitLabels(playerPits);
        for (int i = 0; i < playerPitLabels.length; i++) {
            for (int j = 0; j < playerPitLabels[0].length; j++) {
                if (playerPitLabels[i][j] == pitLabel) {
                    coordinates[0] = i;
                    coordinates[1] = j;
                }
            }
        }
        return coordinates;
    }

    /**
     * Returns the pit across the board from the selected pit.
     *
     * @param pit char
     * @param playersPits int[][]
     * @return char
     */
    public static char getOpposingPit(char pit, int[][] playersPits) {
        int[] coordinates = pit2Coordinates(pit, playersPits);
        if (coordinates[0] == 0) {
            int number = pit + playersPits[0].length;
            return (char) number;
        } else {
            int number = pit - playersPits[0].length;
            return (char) number;
        }
    }

    /**
     * Determines if the selected pit is on the player's side of the board.
     *
     * @param player int
     * @param pit pit
     * @param playersPits int[][]
     * @return boolean
     */
    public static boolean isPitInPlayerRow(int player, char pit, int[][] playersPits) {
        int[] coordinates = pit2Coordinates(pit, playersPits);
        if (coordinates[0] == (player - 1)) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Moves the selected pit counter-clockwise around the board.
     *
     * @param currentPit char
     * @param playersPits int[][]
     * @return char
     */
    public static char nextPit(char currentPit, int[][] playersPits) {
        int[] coordinates = pit2Coordinates(currentPit, playersPits);
        //char letter = currentPit;
        if (coordinates[0] == 0) {
            if (coordinates[1] > 0) {
                int number = (int) currentPit;
                number = number - 1;
                currentPit = (char) number;
                return currentPit;
            } else {
                return getOpposingPit(currentPit, playersPits);
            }
        } else {
            if (coordinates[1] < playersPits[0].length - 1) {
                int number = (int) currentPit;
                number = number + 1;
                currentPit = (char) number;
                return currentPit;
            } else {
                return getOpposingPit(currentPit, playersPits);
            }
        }
    }

    /**
     * Given a pit label, it gives the number of seeds in that pit.
     *
     * @param pit char
     * @param playersPits int[][]
     * @return int
     */
    public static int getPitSeedCount(char pit, int[][] playersPits) {
        int[] coordinates = pit2Coordinates(pit, playersPits);
        return playersPits[coordinates[0]][coordinates[1]];
    }

    /**
     * Sows the seeds during a player's turn.
     *
     * @param pickPit char
     * @param playersPits int[][]
     * @return char
     */
    public static char singleSow(char pickPit, int[][] playersPits) {
        int[] coordinates = pit2Coordinates(pickPit, playersPits);
        int count = playersPits[coordinates[0]][coordinates[1]];
        playersPits[coordinates[0]][coordinates[1]] = 0;
        for (int i = 0; i < count; i++) {
            char nextPit = nextPit(pickPit, playersPits);
            int[] nextPitCoordinate = pit2Coordinates(nextPit, playersPits);
            playersPits[nextPitCoordinate[0]][nextPitCoordinate[1]]++;
            pickPit = nextPit;
        }
        return pickPit;
    }

    /**
     * checks to see if the player whose turn it is can make a move.
     *
     * @param playersPits int[][]
     * @param isPlayer1Turn boolean
     * @return boolean
     */
    public static boolean checkEndGame(int[][] playersPits, boolean isPlayer1Turn) {
        char[][] pitLabels = playerPitLabels(playersPits);
        if (isPlayer1Turn) {
            int emptyPits = 0;
            for (int i = 0; i < pitLabels[0].length; i++) {
                if (getPitSeedCount(pitLabels[0][i], playersPits) == 0) {
                    emptyPits++;
                }
            }
            if (emptyPits == pitLabels[0].length) {
                return true;
            }
        } else {
            int emptyPits = 0;
            for (int i = 0; i < pitLabels[0].length; i++) {
                if (getPitSeedCount(pitLabels[1][i], playersPits) == 0) {
                    emptyPits++;
                }
            }
            if (emptyPits == pitLabels[0].length) {
                return true;
            }
        }
        return false;
    }

    /**
     * returns the sum of all pits on the board.
     *
     * @param playersPits int[][]
     * @return int
     */
    public static int totalSeedsOnBoard(int[][] playersPits) {
        int total = 0;
        char[][] pitLabels = playerPitLabels(playersPits);
        for (int i = 0; i < playersPits.length; i++) {
            for (int j = 0; j < playersPits[0].length; j++) {
                total = total + getPitSeedCount(pitLabels[i][j], playersPits);
            }
        }
        return total;
    }

    /**
     * clears all of the seeds in the pits.
     *
     * @param playersPits int[][]
     */
    public static void clearBoard(int[][] playersPits) {
        for (int i = 0; i < playersPits.length; i++) {
            for (int j = 0; j < playersPits[0].length; j++) {
                playersPits[i][j] = 0;
            }
        }
    }

    /**
     * plays the game endodoi.
     *
     * @param playersPits  int[][]
     * @param player1Store int
     * @param player2Store int
     * @param isPlayer1Turn boolean
     */
    public static void playGame(int[][] playersPits, int player1Store,
                                int player2Store, boolean isPlayer1Turn) {
        Scanner scanner = new Scanner(System.in);
        int player = 0;
        char pit = ' ';
        int pitValue;
        int[] coord;
        char oppPit;
        int oppPitValue;
        int[] oppCoord;
        int captured;
        int lap = 1;


        System.out.println("Starting game of Endodoi");
        if (isPlayer1Turn) {
            drawBoard(playersPits, player1Store, player2Store, pit, 1);
        } else {
            drawBoard(playersPits, player1Store, player2Store, pit, 2);
        }
        while (!checkEndGame(playersPits, isPlayer1Turn)) {
            if (isPlayer1Turn) {
                player = 1;
                System.out.println("Player 1 chose a pit:");
                pit = scanner.next().charAt(0);
                while (isPlayer1Turn) {
                    pitValue = getPitSeedCount(pit, playersPits);
                    if (pit == '!') {
                        System.out.println("Game ended");
                        break;
                    } else if (!isPitInPlayerRow(player, pit, playersPits) && lap == 1) {
                        System.out.println("Not a valid pit. Please pick again.");
                        System.out.println("Player 1 chose a pit:");
                        pit = scanner.next().charAt(0);
                    } else if (pitValue == 0) {
                        System.out.println("Can't pick from an empty pit. Please pick again.");
                        System.out.println("Player " + player + " chose a pit:");
                        pit = scanner.next().charAt(0);
                    } else {
                        pit = singleSow(pit, playersPits);
                        drawBoard(playersPits, player1Store, player2Store, pit, 1);
                        oppPit = getOpposingPit(pit, playersPits);
                        coord = pit2Coordinates(pit, playersPits);
                        oppCoord = pit2Coordinates(oppPit, playersPits);
                        pitValue = getPitSeedCount(pit, playersPits);
                        oppPitValue = getPitSeedCount(oppPit, playersPits);
                        if (pitValue == 1) {
                            isPlayer1Turn = false;
                            player = 2;
                            if (oppPitValue != 0) {
                                captured = pitValue + oppPitValue;
                                player1Store = player1Store + captured;
                                playersPits[coord[0]][coord[1]] = 0;
                                playersPits[oppCoord[0]][oppCoord[1]] = 0;
                                System.out.println("Player 1's turn ended.");
                                System.out.println("Player 1 captured " + captured + " seeds");
                            } else {
                                System.out.println("Player 1's turn ended.");
                            }
                            drawBoard(playersPits, player1Store, player2Store, ' ', player);
                            lap = 1;
                        } else {
                            System.out.println(
                                    "Sowing ended in non-empty pit. Multi-lap " + lap + ". Resowing seeds...");
                            lap++;
                        }
                    }
                }
            } else {
                player = 2;
                System.out.println("Player 2 chose a pit:");
                pit = scanner.next().charAt(0);
                while (!isPlayer1Turn) {
                    pitValue = getPitSeedCount(pit, playersPits);
                    if (pit == '!') {
                        System.out.println("Game ended");
                        break;
                    } else if (!isPitInPlayerRow(player, pit, playersPits) && lap == 1) {
                        System.out.println("Not a valid pit. Please pick again.");
                        System.out.println("Player 2 chose a pit:");
                        pit = scanner.next().charAt(0);
                    } else if (pitValue == 0) {
                        System.out.println("Can't pick from an empty pit. Please pick again.");
                        System.out.println("Player 2 chose a pit:");
                        pit = scanner.next().charAt(0);
                    } else {
                        pit = singleSow(pit, playersPits);
                        drawBoard(playersPits, player1Store, player2Store, pit, 2);
                        oppPit = getOpposingPit(pit, playersPits);
                        coord = pit2Coordinates(pit, playersPits);
                        oppCoord = pit2Coordinates(oppPit, playersPits);
                        pitValue = getPitSeedCount(pit, playersPits);
                        oppPitValue = getPitSeedCount(oppPit, playersPits);
                        if (pitValue == 1) {
                            player = 1;
                            isPlayer1Turn = true;
                            if (oppPitValue != 0) {
                                captured = pitValue + oppPitValue;
                                player2Store = player2Store + captured;
                                playersPits[coord[0]][coord[1]] = 0;
                                playersPits[oppCoord[0]][oppCoord[1]] = 0;
                                System.out.println("Player 2's turn ended.");
                                System.out.println("Player 2 captured " + captured + " seeds");
                            } else {
                                System.out.println("Player 2's turn ended.");
                            }
                            drawBoard(playersPits, player1Store, player2Store, ' ', 1);
                            lap = 1;
                        } else {
                            System.out.println(
                                    "Sowing ended in non-empty pit. Multi-lap " + lap + ". Resowing seeds...");
                            lap++;
                        }
                    }
                }
            }
            if (pit == '!') {
                break;
            }
        } if (pit != '!') {
            int remSeeds = totalSeedsOnBoard(playersPits);
            pit = ' ';
            System.out.println("Player " + player + " can't move.");
            if (player == 1) {
                System.out.println("The remaining " + remSeeds + " seeds go to Player 2");
                player2Store += remSeeds;
            } else {
                System.out.println("The remaining " + remSeeds + " seeds go to Player 1");
                player1Store += remSeeds;
            }
            clearBoard(playersPits);
            drawBoard(playersPits, player1Store, player2Store, pit, -1);
            if (player1Store > player2Store) {
                System.out.println("Player 1 is the winner!");
            } else if (player1Store < player2Store) {
                System.out.println("Player 2 is the winner!");
            } else {
                System.out.println("It was a draw!");
            }
        }
        scanner.close();
    }

    /**
     * for testing the application.
     *
     * @param args args
     */
    
     public static void main(String[] args) {
        int[][] playerPits = createNewPits(3, 2);
        playGame(playerPits, 3, 2, true);
    }
}