import java.util.ArrayList;

/**
 * @author Nick Snyder
 * @version 9 December 2021
 *
 * NimState class
 */
public class NimState implements State {

    int[] stacks;
    boolean pt;

    /**
     * Move inner class.
     */
    public static class Move implements State.Move {

        int stack;
        int num;

        /**
         * Constructor.
         *
         * @param stack int
         * @param num int
         */
        public Move(int stack, int num) {
            this.stack = stack;
            this.num = num;
        }

        /**
         * Equals.
         *
         * @param o Object
         * @return boolean
         */
        public boolean equals(Object o) {
            if (o instanceof Move) {
                return ((Move) o).stack == stack && ((Move) o).num == num;
            } else {
                return false;
            }
        }

        @Override
        public String toString() {
            return "Taking " + num + " from stack " + stack;
        }
    }

    /**
     * Constructor.
     *
     * @param n int
     * @param pt boolean
     */
    public NimState(int n, boolean pt) {
        stacks = new int[n];

        for (int i = 0; i < getStacks().length; i++) {
            stacks[i] = i + 1;
        }

        this.pt = pt;
    }

    /**
     * Copy constructor.
     *
     * @param stacks int[]
     * @param pt boolean
     */
    public NimState(int[] stacks, boolean pt) {

        this.stacks = new int[stacks.length];

        for (int i = 0; i < getStacks().length; i++) {
            System.arraycopy(stacks, 0, this.stacks, 0, getStacks().length);
        }

        this.pt = pt;
    }

    /**
     * Returns the stack.
     *
     * @return int[]
     */
    public int[] getStacks() {
        return stacks;
    }

    /**
     * Returns whether it is the human player's turn or not.
     *
     * @return true if it is the human player's turn.
     */
    @Override
    public boolean isPlayerTurn() {
        return pt;
    }

    @Override
    public String toString() {
        String ret = "";
        for (int i = 0; i < getStacks().length; i++) {
            ret += (i + 1) + ": ";
            for (int j = 0; j < stacks[i]; j++) {
                ret += "X";
            }
            ret += "\n";
        }
        return ret;
    }

    /**
     * Tests whether the game is over.
     *
     * @return true if game is over, false otherwise.
     */
    @Override
    public boolean gameOver() {
        int sum = 0;
        for (int stack : getStacks()) {
            sum += stack;
        }
        return sum == 0;
    }

    /**
     * Returns the value of an end-game state. Throws an exception if the
     * current state is not an end-game.
     *
     * @return 1 for a win, -1 for a loss.
     */
    @Override
    public int getValue() {
        if (gameOver()) {
            if (isPlayerTurn()) {
                return -1;
            } else {
                return 1;
            }
        }
        throw new IllegalStateException();
    }

    /**
     * Tests whether a move is valid and performs it if so.
     *
     * @param move Move The move to be done.
     * @return true if move was valid, false otherwise.
     */
    @Override
    public boolean doMove(State.Move move) {

        Move m = (Move) move;

        // if it was a valid move
        if (m.stack > stacks.length || m.stack <= 0 || m.num <= 0 || m.num > stacks[m.stack - 1]) {

            return false;

        } else {
            // changing the value in the stack for this state
            stacks[m.stack - 1] -= m.num;

            // change the value of playerTurn
            pt = !pt;

            // return true
            return true;
        }
    }

    /**
     * Undoes the effects of the given move.
     *
     * @param move Move The move to be undone.
     */
    @Override
    public void undoMove(State.Move move) {

        Move m = (Move) move;

        stacks[m.stack - 1] += m.num;

        pt = !pt;
    }

    /**
     * Finds all valid moves from the current state.
     *
     * @return ArrayList of moves.
     */
    @Override
    public ArrayList<State.Move> findAllMoves() {

        ArrayList<State.Move> moves = new ArrayList<>();

        // check all locations in the board
        for (int i = 0; i < stacks.length; i++) {

            int count = stacks[i];

            if (count >= 1) {
                moves.add(new Move(i + 1, 1));
            }
            if (count >= 2) {
                moves.add(new Move(i + 1, 2));
            }
            if (count >= 3) {
                moves.add(new Move(i + 1, 3));
            }
        }
        return moves;
    }
}
