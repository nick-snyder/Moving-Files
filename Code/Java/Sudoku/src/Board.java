import java.util.Scanner;

/**
 * @author Nick Snyder
 * @version 12 November 2021
 */
public class Board {

    public static int[][] board;

    /**
     * Constructor for the Board class.
     *
     * @param sc Scanner
     */
    public Board(Scanner sc) {
        board = readBoard(sc);
    }

    /**
     * Uses the provided Scanner to read the board and return a 2D integer array with the appropriate values.
     * Input should be 9 rows of values with 9 characters each.
     * These characters will be 1-9 to indicate a fixed number in the starting board,
     * or a - (dash) to indicate an empty location. A value of 0 indicates an empty space in the returned array.
     * Should return null if the board was invalid
     *
     * @param sc Scanner
     * @return int[][]
     */
    public static int[][] readBoard(Scanner sc) {

        // assign board to an empty 9x9 int 2d array
        board = new int[9][9];

        // declare String variable
        String line;

        // for every row (9)
        for (int i = 0; i < 9; i++) {

            // store next line to String
            line = sc.nextLine();

            if (line.length() != 9) {
                return null;
            }

            // for every column in row (9)
            for (int j = 0; j < 9; j++) {

                // store char at index
                char c = line.charAt(j);

                if (c == '-') {
                    board[i][j] = 0;
                } else if ("1234567890".indexOf(c) != -1) {
                    board[i][j] = Character.getNumericValue(c);
                } else {
                    return null;
                }
            }
        }

        // return the board array
        return board;
    }

    /**
     * Returns the value at row, col in the board.
     *
     * @param row int
     * @param col int
     * @return int
     */
    public int get(int row, int col) {
        return board[row][col];
    }

    /**
     * Sets the value at row, col in the board.
     *
     * @param row int
     * @param col int
     * @param value int
     */
    public void set(int row, int col, int value) {
        board[row][col] = value;
    }

    /**
     * Returns true if number was already contained in row.
     *
     * @param row int
     * @param number int
     * @return boolean
     */
    public boolean containsInRow(int row, int number) {

        // for each position in row (9)
        for (int i = 0; i < 9; i++) {

            // if number matches board value at index
            if (number == get(row, i)) {

                // match found -> true
                return true;
            }
        }

        // match found -> false
        return false;
    }

    /**
     * Returns true if number was already contained in column.
     *
     * @param col int
     * @param number int
     * @return boolean
     */
    public boolean containsInCol(int col, int number) {

        // for each position in column (9)
        for (int i = 0; i < 9; i++) {

            // if number matches board value at index
            if (number == get(i, col)) {

                // match found -> true
                return true;
            }
        }

        // match found -> false
        return false;
    }

    /**
     * Returns true if number was already contained in the 3x3 box containing row, column, false otherwise.
     *
     * @param row int
     * @param col int
     * @param number int
     * @return boolean
     */
    public boolean containsInBox(int row, int col, int number) {

        // initialize bounds in later for-loop
        int num = (int) Math.sqrt(board.length);
        int boxRow = row - row % num;
        int boxCol = col - col % num;

        // for each position in row (3)
        for (int i = boxRow; i < boxRow + num; i++) {

            // for each position in column (3)
            for (int j = boxCol; j < boxCol + num; j++) {

                // if number matches board at index
                if (number == get(i, j)) {

                    // return true
                    return true;
                }
            }
        }

        // return false
        return false;
    }

    /**
     * For number to be allowed it should satisfy all the rules for row,
     * column, and 3x3 box. It should also return false if the location has a fixed value.
     *
     * @param row int
     * @param col int
     * @param number int
     * @return boolean
     */
    public boolean isAllowed(int row, int col, int number) {

        // if board at index does not equal 0
        if (get(row, col) != 0) {

            // return false
            return false;
        }

        // return true if all cases return false
        return !containsInRow(row, number) && !containsInCol(col, number) && !containsInBox(row, col, number);
    }

    @Override
    public String toString() {

        // initialize stringBuilder
        StringBuilder ret = new StringBuilder();

        // for each position in row (9)
        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0) {

                // horizontal border
                ret.append("+-------+-------+-------+\n");
            }

            // for each position in column (9)
            for (int j = 0; j < 9; j++) {
                if (j % 3 == 0) {

                    // segment of vertical border
                    ret.append("| ");
                }

                // if the board at index equals zero
                if (get(i, j) == 0) {

                    // add dash at index
                    ret.append("-");

                } else {

                    // add number at index
                    ret.append(get(i, j));
                }

                // space between each board index
                ret.append(" ");
            }

            // end of row vertical border and new line
            ret.append("|\n");
        }

        // bottom border
        ret.append("+-------+-------+-------+");

        // cast stringBuilder to String and return
        return ret.toString();
    }
}
