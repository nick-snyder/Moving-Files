import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 * This class does the work of solving the Sudoku puzzle,
 * as well as containing the main method to provide a text-based user interface.
 * Stores a Board object which it uses in solving. Tracks statistics about the solving process:
 * the number of recursive calls made, and the number of "backups" that had to be done.
 *
 * @author Nick Snyder
 * @version 12 November 2021
 */
public class Sudoku {

    public Board board;

    public int recursionCount;
    public int backupCount;

    /**
     * Constructor for the Sudoku class.
     *
     * @param sc Scanner
     */
    public Sudoku(Scanner sc) {
        this.board = new Board(sc);
        recursionCount = 0;
        backupCount = 0;
    }

    /**
     * Recursively solves the board from the current configuration,
     * using the backtracking algorithm described above.
     *
     * @param loc Location
     * @return boolean
     */
    public boolean solve(Location loc) {

        // iterate recursionCount
        recursionCount++;

        boolean good = false;

        if (loc == null) {
            return true;
        }

        int row = loc.getRow();
        int col = loc.getColumn();
        int value = board.get(row, col);

        if (value != 0) {
            good = solve(loc.next());
        } else {
            for (int val = 1; val < 10 && !good; val++) {
                board.set(row, col, 0);
                if (board.isAllowed(row, col, val)) {
                    board.set(loc.getRow(), loc.getColumn(), val);
                    good = solve(loc.next());
                }
            }
            if (!good) {
                board.set(loc.getRow(), loc.getColumn(), 0);
                backupCount++;
            }
        }
        return good;
    }

    /**
     * Returns the recursion count after the puzzle has been solved.
     *
     * @return int
     */
    public int getRecursionCount() {
        return recursionCount;
    }

    /**
     * Returns the backup count after the puzzle has been solved.
     *
     * @return int
     */
    public int getBackupCount() {
        return backupCount;
    }

    /**
     * Returns the Sudoku board.
     *
     * @return Board
     */
    public Board getBoard() {
        return board;
    }

    /**
     * Prompts the user for a file name, creates a Scanner using that file,
     * creates a Sudoku object, prints the initial board,
     * calls the solve method, and then prints the results,
     * including the recursion count and backup count.
     *
     * @param args String[]
     */
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.println("Enter the path to the sudoku file:");

        String filename = sc.nextLine();

        File file = new File(filename);

        try {

            Scanner boardScanner = new Scanner(file);

            Sudoku sudoku = new Sudoku(boardScanner);

            System.out.println("Initial configuration of the sudoku");
            System.out.println(sudoku.getBoard());

            Location location = new Location(0, 0);

            if (sudoku.solve(location)) {
                System.out.println("Successful!");
                System.out.println("Final configuration of the sudoku");
                System.out.println(sudoku.getBoard());
                System.out.println("Recursion count = " + sudoku.getRecursionCount());
                System.out.println("Backup count = " + sudoku.getBackupCount());
            } else {
                System.out.println("Sudoku is unsolvable");
            }

        // input does not match known file name
        } catch (FileNotFoundException e) {
            System.out.println("File was not found.");
        }
        sc.close();
    }
}
