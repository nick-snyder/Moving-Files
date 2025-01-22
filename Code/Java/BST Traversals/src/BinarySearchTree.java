import java.util.*;

public class BinarySearchTree {
    //-------------------- instance variables ---------------------
    private Node _root;
    private int _size;
    
    //-------------------- constructors --------------------------
    /**
     * Construct an empty tree with no nodes.
     */
    public BinarySearchTree() {
        _root = null;
        _size = 0;
    }

    /**
     * Helper method for inOrder( Node ).
     *
     * @return String all items from the tree in order
     */
    public String inOrder() {
        String ret = "";
        if (this._root != null) {
            ret += this.inOrder(this._root.left);
            ret += this._root.data + ", ";
            ret += this.inOrder(this._root.right);
        }
        return ret;
    }

    /**
     * Generate a string containing all items from a subtree by 
     * traversing them in order.
     *
     * @param n Node the root of the subtree to be traversed.
     * @return String all items from the tree in order
     */
    public String inOrder(Node n) {
        String ret = "";
        if (n != null) {
            ret += this.inOrder(n.left);
            ret += n.data + ", ";
            ret += this.inOrder(n.right);
        }
        return ret;
    }

    /**
     * The leftmost node from the subtree rooted at n.
     *
     * @param n Node the root of the subtree.
     * @return Node the leftmost node under n.
     */
    public Node leftMost(Node n) {

        if (n == null) {
            return null;
        }

        if (n.left != null) {
            return leftMost(n.left);
        } else {
            return n;
        }
    }

    /**
     * The ancestor (parent or higher) which hasn't been processed yet.
     *
     * @param n Node the root of the subtree.
     * @return Node the unfinished ancestor of n.
     */
    public Node unfinishedAncestor( Node n ){

        if (n.parent == null) {
            return null;
        } else if (n.parent.right != n) {
            return n.parent;
        } else {
            return unfinishedAncestor(n.parent);
        }
    }

    /**
     * An iterator class that traverses the tree in order.
     */
    private class InOrderIterator implements Iterator{

        private Node next;

        /**
         * Constructor for the iterator.
         */
        public InOrderIterator() {
            next = leftMost(_root);
        }

        /**
         * Moves to the next node and returns the data from 
         * the current node.
         *
         * @return Data the data from the current node.
         */
        public Data next(){

            if (next == null) {
                throw new NoSuchElementException();
            }
        
            Node curr = next;
            if (next.right != null) {
                next = next.right;
                while (next.left != null) {
                    next = next.left;
                }
                return  curr.data;
            }
            while (true) {
                if (next.parent == null) {
                    next = null;
                    return curr.data;
                }
                if (next.parent.left == next) {
                    next = next.parent;
                    return curr.data;
                }
                next = next.parent;
            }
        }

        /**
         * Indicates whether there is data left to traverse in the tree.
         *
         * @return boolean true if there is data left, false otherwise
         */
        public boolean hasNext() {
            return next != null;
        }
    }

    
    //////////////////////////////////////////////////////////////////
    // MAKE NO CHANGES BELOW HERE
    //////////////////////////////////////////////////////////////////
    

    //--------------------- iterator -----------------------------------
    /**
     * Returns a new InOrderIterator from this BST.
     */
    public InOrderIterator iterator() {
        return new InOrderIterator();
    }
    
    //--------------------- add -----------------------------------
    /**
     * Add a node to the tree in its proper position determined by the
     * "key" field of the Data object. This method uses the addNode 
     * recursive utility method.
     * 
     * @param data Data         Data object to be added to the tree.
     */
    public void add(Data data) {
        boolean added = true;
        if (_root == null) {
            _root = new Node(data);
        } else {
            added = addNode( _root, data);
        }
        if (added) {
            _size++;
        }
    }
    
    //------------------ addNode( Node, Data ) -----------------------
    /**
     * A recursive method to add a new Data object to the subtree
     * rooted at the first argument.
     * 
     * @param parent Node       subtree to which Data is to be added
     * @param newOne Data       Data object to be added to the tree
     * @return boolean          true if add was successful
     */
    private boolean addNode(Node parent, Data newOne) {
        boolean added = true;
        int cmp = newOne.compareTo(parent.data);
        if (cmp < 0) {
            if (parent.left != null) {
                added = addNode(parent.left, newOne);
            } else {
                parent.left = new Node(newOne);
                parent.left.parent = parent;
            }
        } else if (cmp == 0) {
            System.err.println("== key found: Not adding: " + newOne);
            added = false;
        } else {
            if (parent.right != null) {
                added = addNode(parent.right, newOne);
            } else {
                parent.right = new Node(newOne);
                parent.right.parent = parent;
            }
        }
        return added;
    }
    //-------------------- size(  ) -------------------------
    /**
     * Return the number of nodes in the tree.
     * @return int   size of tree
     */
    public int size() {
        return _size;
    }
    //-------------------------- toString() -------------------------
    /**
     * Generate a string representation of the tree.
     * 
     * @return String       a string representation of the tree.
     */
    public String toString() {
        return toString(_root, "  ", "=");        
    }
    
    /**
     * Recursively generate a string representation for a Node of a tree;
     *    indent is increased for increasing depth.
     * Branch is a short string that prefixes each node indicating
     *        whether the node is a left (L) or right (R) child.
     * @return String        string rep of subtree
     * @param n Node         subtree to convert to string
     * @param indent String  prefix string for indentation level
     * @param branch String  (L) or (R)
     */
    private String toString(Node n, String indent, String branch) {
        String s = "";
        if (n != null) {
            String prefix = indent.substring( 0, indent.length() - 2 ) 
                                  + branch;
            s += prefix + n.data.toString() + "\n";
            if (n.left != null) {
                s += toString(n.left, indent + "  ", "L ");
            }
            if ( n.right != null ) {
                s += toString(n.right, indent + "  ", "R ");
            }
        }
        return s;
    }
    //-------------------- findNode( String ) -----------------------
    /**
     * Given a key value, search the tree to find the node that has
     * that key value, if it exists.
     * 
     * Return the Data object from the node or null.
     * @param key String
     * @return Node
     */
    public Node findNode( String key ) {
        Data found = null;
        Node cur = _root;
        while (cur != null && found == null) {
            int cmp = key.compareTo(cur.data.key);
            if (cmp == 0) {
                found = cur.data;
            } else if (cmp < 0) {
                cur = cur.left;
            } else {
                cur = cur.right;
            }
        }
        return cur;
    }
    //+++++++++++++++++++++++ inner class Node ++++++++++++++++++++++
    /**
     * The Node class does not have to be seen outside this class, so
     * it is private.
     * @author rdb
     */
    public class Node {
        //-------------- instance variables ---------------------------
        Data data;
        Node left;
        Node right;
        Node parent;
        
        //--------------- constructor --------------------------------
        /**
         * Construct a node with Data.
         * 
         * @param  d Data    data for the node.
         */
        public Node(Data d) {
            data = d;
            left = null;
            right = null;
            parent = null;
        }
    }
}
