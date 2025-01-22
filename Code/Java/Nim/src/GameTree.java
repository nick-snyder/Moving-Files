import java.util.ArrayList;

/**
 * @author Nick Snyder
 * @version 9 December 2021
 *
 * Game Tree.
 */
public class GameTree {

    Node root;
    int size;

    /**
     * Node inner class.
     */
    public class Node {
        //-------------- instance variables ---------------------------
        State.Move move;
        Node[] children;
        Node bestChild;
        int value;

        //--------------- constructor --------------------------------
        /**
         * Construct a node with Data.
         *
         * @param m State.Move
         */
        public Node(State.Move m) {
            move = m;
        }

        /**
         * Returns value.
         *
         * @return int
         */
        public int getValue() {
            return value;
        }

        /**
         * Returns move.
         *
         * @return State.Move
         */
        public State.Move getMove() {
            return move;
        }

        /**
         * Returns the best child.
         *
         * @return Node
         */
        public Node getBestChild() {
            return bestChild;
        }

        /**
         * Finds child associated with specified move.
         *
         * @param m State.Move
         * @return Node
         */
        public Node findChild(State.Move m) {
            for (Node child : children) {
                if (child.getMove().equals(m)) {
                    return child;
                }
            }
            return null;
        }

        /**
         * Returns best prediction.
         *
         * @return String
         */
        public String getPrediction() {

            if (value == 1) {
                return "computer";
            } else if (value == -1) {
                return "player";
            } else {
                return "no one";
            }
        }
    }

    /**
     * Constructor for GameTree.
     *
     * @param start State
     */
    public GameTree(State start) {
        size = 0;
        root = buildTree(start, null);
    }

    /**
     * Returns root.
     *
     * @return Node
     */
    public Node getRoot() {
        return root;
    }

    /**
     * Builds tree recursively.
     *
     * @param state State
     * @param move State.Move
     * @return Node
     */
    public Node buildTree(State state, State.Move move) {


        Node node = new Node(move);
        size++;
        ArrayList<State.Move> moves = state.findAllMoves();

        if (moves.size() == 0) {
            node.value = state.getValue();
        }

        node.children = new Node[moves.size()];

        for (int i = 0; i < moves.size(); i++) {
            state.doMove(moves.get(i));
            Node child = buildTree(state, moves.get(i));
            state.undoMove(moves.get(i));
            node.children[i] = child;
            if (node.bestChild == null) {
                node.value = child.value;
                node.bestChild = child;
            } else if (!state.isPlayerTurn() && child.value > node.value) {
                node.value = child.value;
                node.bestChild = child;
            } else if (state.isPlayerTurn() && child.value < node.value) {
                node.value = child.value;
                node.bestChild = child;
            }
        }
        return node;
    }

    /**
     * Returns size.
     *
     * @return int
     */
    public int getSize() {
        return size;
    }
}
