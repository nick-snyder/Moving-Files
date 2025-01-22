import java.util.ArrayList;
import java.util.Objects;

public class TicTacToeState implements State {

    String[][] board;
    boolean playerTurn;

    /**
     * Default constructor. Creates a starting game state.
     * Computer will be X, and player will be O.
     *
     * @param turn Indicates whether it is the player's turn first.
     */
    public TicTacToeState(boolean turn) {
        board = new String[3][3];
        this.playerTurn = turn;
    }

    /**
     * Copy constructor. Creates a new state by
     * copying the values in the board and turn parameters.
     * Computer will be X, and player will be O.
     *
     * @param board The current game board to be copied.
     * @param turn Indicates whether it is the player's turn in this state.
     */
    public TicTacToeState(String[][] board, boolean turn) {
        this.board = new String[3][3];

        for (int r = 0; r < board.length; r++) {
            for (int c = 0; c < board[r].length; c++) {
                this.board[r][c] = board[r][c];
            }
        }
        this.playerTurn = turn;
    }

    /**
     * Returns the mark for the player whose turn it is in this state.
     *
     * @return "O" if playerTurn is true, "X" otherwise.
     */
    public String getMark() {
        return playerTurn ? "O" : "X";
    }

    /**
     * Returns the board for this state.
     *
     * @return The board.
     */
    public String[][] getBoard() {
        return board;
    }

    /**
     * Returns whether it is the human player's turn or not.
     *
     * @return true if it is the human player's turn. (The current turn is "O".)
     */
    public boolean isPlayerTurn() {
        return playerTurn;
    }

    /**
     * Returns a string representation of this state.
     *
     * @return The string representing this state.
     */
    public String toString() {
        String ret = "";
        String bar = " -------------\n";
        ret += bar;

        for (int r = 0; r < board.length; r++) {
            for (int c = 0; c < board[r].length; c++) {
                if (board[r][c] == null) {
                    ret += " |  ";
                } else {
                    ret += " | " + board[r][c];
                }
            }
            ret += " |\n";
            ret += bar;
        }
        return ret;
    }

    /**
     * Finds all legal moves from the current state.
     *
     * @return ArrayList of moves.
     */
    public ArrayList<State.Move> findAllMoves() {

        // if its current value is not X or O
        if (!getMark().equals("X") || !getMark().equals("O")) {

            ArrayList<State.Move> moves = new ArrayList<>();

            // check all locations in the board
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == null) {

                        // create a move for that location
                        State.Move move = new Move(i, j);
                        moves.add(move);
                    }
                }
            }
            return moves;
        } else {
            return null;
        }
    }

    /**
     * Tests whether the game is over.
     *
     * @return true if game is over, false otherwise.
     */
    public boolean gameOver() {
        return checkWinner() || isBoardFull();
    }

    private boolean checkWinner() {
        for (int i = 0; i < 3; i++) {
            if (Objects.equals(board[i][0], board[i][1]) && 
                Objects.equals(board[i][1], board[i][2])) {
                return board[i][0] != null;
            }
        }
        for (int i = 0; i < 3; i++) {
            if (Objects.equals(board[0][i], board[1][i]) && 
                Objects.equals(board[1][i], board[2][i])) {
                return board[0][i] != null;
            }
        }
        if (Objects.equals(board[0][0], board[1][1]) && 
            Objects.equals(board[1][1], board[2][2])) {
            return board[1][1] != null;
        }
        if (Objects.equals(board[0][2], board[1][1]) && 
            Objects.equals(board[1][1], board[2][0])) {
            return board[1][1] != null;
        }
        return false;
    }

    private boolean isBoardFull() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == null) {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * Returns the value of an end-game state. Throws a new IllegalStateException if the
     * current state is not an end-game.
     *
     * @return 1 for a win for X, -1 for a loss.
     */
    public int getValue() {

        if (checkWinner()) {
            if (isPlayerTurn()) {
                return 1;
            } else {
                return -1;
            }
        }
        if (isBoardFull()) {
            return 0;
        }
        throw new IllegalStateException();
    }

    /**
     * Tests whether a move is legal and performs it if so.
     *
     * @param m Move The move to be done.
     * @return true if move was legal, false otherwise.
     */
    public boolean doMove(State.Move m) {

        TicTacToeState.Move move = (TicTacToeState.Move) m;

        // if it was a valid move
        if (((move.r < 3 && move.r >= 0) && 
            (move.c < 3 && move.c >= 0)) && 
            (board[move.r][move.c] == null)) {

            // changing the value in the board for this state
            board[move.r][move.c] = getMark();

            // change the value of playerTurn
            playerTurn = !isPlayerTurn();

            // return true
            return true;
        }
        return false;
    }

    /**
     * Undoes the effects of the given move.
     *
     * @param m Move The move to be undone.
     */
    public void undoMove(State.Move m) {

        TicTacToeState.Move move = (TicTacToeState.Move) m;

        // changing the value in the board for this state
        board[move.r][move.c] = null;
    }

    public class Move implements State.Move {

        int r, c;

        /**
         * Default constructor.
         */
        public Move( int r, int c ) {
            this.r = r;
            this.c = c;
        }

        /**
         * Returns a string representation of this move.
         *
         * @return The string representing this move.
         */
        public String toString() {
            return "row " + r + " column " + c;
        }

        /**
         * Determine whether this move is equal to another object.
         *
         * @return true if all data from the move matches, false otherwise.
         */
        public boolean equals(Object o) {
            if (o instanceof Move) {
                Move m = (Move) o;
                return m.r == r && m.c == c;
            }
            return false;
        }
    }
}
