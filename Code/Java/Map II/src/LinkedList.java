import java.util.Scanner;

/**
 * @author Nicholas Snyder
 * @version 27 October 2021
 *
 * @param <T> list
 */
public class LinkedList<T> extends List<T> {

    private Node head;
    private Node tail;

    /**
     * The constructor for LinkedList. It should initialize any necessary fields.
     */
    public LinkedList() {
        this.head = getHead();
        this.tail = getTail();
    }

    /**
     * Gets head.
     *
     * @return Node
     */
    public Node getHead() {
        return head;
    }

    /**
     * Gets tail.
     *
     * @return Node
     */
    public Node getTail() {
        return tail;
    }

    /**
     * Appends the specified value to the end of this list.
     *
     * @param value T The value to add
     * @return boolean True if the value is inserted, false otherwise
     */
    @Override
    boolean add(T value) {

        Node node = new Node(value);

        if (!contains(value)) {
            if (this.tail == null || this.head == null) {
                this.head = node;
            } else {
                tail.next = node;
                node.prev = tail;
            }
            tail = node;
            return true;
        } else {
            return false;
        }
    }

    /**
     * Inserts the specified value at the specified position in this list.
     *
     * @param index Integer The index at which to insert
     * @param value T The value to insert
     */
    @Override
    void add(int index, T value) {

        Node temp = this.head;
        Node node = new Node(value);
        int i = 0;

        if (!contains(value)) {
            if (index == 0) {
                if (size() == 0) {

                    this.head = node;
                    this.tail = node;

                } else {

                    node.next = this.head;
                    this.head.prev = node;
                    this.head = node;
                }

            } else if (index == size()) {

                this.tail.next = node;
                node.prev = this.tail;
                this.tail = node;

            } else if (index == 1) {

                Node temp1 = this.head.next;
                node.next = temp1;
                node.prev = this.head;
                this.head.next = node;
                temp1.prev = node;

            } else if (index == size() - 1) {

                add(value);

            } else {

                while (temp != null) {
                    if (index == i) {

                        node.prev = temp.prev;
                        temp.prev = node;
                        node.prev.next = node;
                        node.next = temp;
                    }
                    temp = temp.next;
                    i++;
                }
            }
        }
    }

    @Override
    public String toString() {

        StringBuilder ret = new StringBuilder("[");
        Node temp = head;

        while (temp != null) {
            if (temp.next != null) {
                ret.append(temp.value).append(", ");
            } else {
                ret.append(temp.value);
            }
            temp = temp.next;
        }

        ret.append("]");
        return ret.toString();
    }

    /**
     * Removes all the elements from this list.
     */
    @Override
    void clear() {

        head = null;

//        if (size() > 1) {
//            head.next.prev = null;
//            head.next = null;
//
//            tail.prev.next = null;
//            tail.prev = null;
//
//            head = null;
//            tail = null;
//        } else {
//            remove(0);
//        }
    }

    /**
     * Returns the element at the specified position in this list.
     *
     * @param index Integer The index at which to insert
     * @return T
     */
    @Override
    T get(int index) {

        Node temp = this.head;
        int i = 0;

        while (temp != null) {
            if (index == i) {

                return temp.value;
            }
            ++i;
            temp = temp.next;
        }
        return null;
    }

    /**
     * Get the list entry corresponding to the value provided in the parameter.
     *
     * @param o to search for
     * @return T matching data in the list
     */
    @Override
    T get(Object o) {

        Node temp = this.head;
        Node ret = temp;
        boolean bool = true;

        while (temp != null) {

            if (temp.value.equals(o)) {
                bool = false;
                ret = temp;
            }
            temp = temp.next;
        }

        if (bool) {
            return null;
        } else {
            return ret.value;
        }
    }

    /**
     * Returns true if this list contains the specified element.
     *
     * @param o Object The element to check if present in the list
     * @return boolean
     */
    @Override
    boolean contains(Object o) {

        Node node = new Node(get(o));
        Node temp = this.head;
        boolean bool = false;

        while (temp != null) {
            if (temp.value.equals(node.value)) {

                bool = true;
                break;
            }
            temp = temp.next;
        }
        return bool;
    }

    /**
     * Returns true if this list contains no elements.
     *
     * @return true if this list contains no elements
     */
    @Override
    boolean isEmpty() {

        return this.head == null || this.tail == null;
    }

    /**
     * Removes the element at the specified position in this list.
     * Returns the element from the list or null if index is invalid.
     *
     * @param index the index of the element to be removed
     * @return the element previously at the specified position or null
     */
    @Override   //bug here
    T remove(int index) {

        Node temp = this.head;
        Node currentNode;

        // if index is within valid nodes
        if ((0 <= index) && (index < this.size())) {

            // if remove first node
            if (index == 0) {

                this.head = temp.next;
                temp.prev = null;
                currentNode = temp;

            // if remove last node
            } else if (index == this.size() - 1) {

                temp = this.tail;
                temp.prev.next = null;
                this.tail = temp.prev;
                currentNode = temp;

            // if remove middle node (supposedly)
            } else {

                Node current = head;    //temp

                for (int i = 0; i < index; i++) {
                    current = current.next;
                }

                current.prev.next = current.next;
                current.next.prev = current.prev;
                currentNode = current;
            }
            return currentNode.value;
        }
        return null;
    }

    /**
     * Removes the first occurrence of the specified element from this
     * list, if it is present.
     * If this list does not contain the element, it is unchanged.
     * Returns true if this list contained the specified element
     * (or equivalently, if this list changed as a result of the call).
     *
     * @param o element to be removed from this list, if present
     * @return true if this list contained the specified element
     */
    @Override
    boolean remove(Object o) {

        int i = 0;

        // if list in empty
        if (isEmpty()) {
            return false;
        } else {

            Node temp = this.head;

            if (contains(o)) {
                while (!temp.value.equals(o)) {

                    temp = temp.next;
                    i++;
                }
                remove(i);
                return true;
            }
        }
        return false;
    }

    /**
     * Returns the number of elements in this list.
     *
     * @return int
     */
    @Override
    int size() {

        Node temp = this.head;
        int i = 0;

        while (temp != null) {

            i++;
            temp = temp.next;
        }
        return i;
    }

    /**
     * Main method.
     *
     * @param args String[]
     */
    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        String command;
        LinkedList<String> list = new LinkedList<>();

        while (true) {
            command = scanner.next();
            if (command.equals("x")) {
                break;
            } else {
                switch (command.substring(0, 1)) {
                    case "a":
                        //add( T value )
                        command = scanner.next();
                        list.add(command);
                        System.out.print(list);
                        break;
                    case "A":
                        //add( int index, T value )
                        int index = Integer.parseInt(scanner.next());
                        String value = scanner.next();
                        list.add(index, value);
                        System.out.print(list);
                        break;
                    case "c":
                        //contains( Object o )
                        Object o = scanner.next();
                        System.out.print(list.contains(o));
                        break;
                    case "C":
                        //clear()
                        list.clear();
                        System.out.print(list);
                        break;
                    case "g":
                        //get( int index )
                        index = Integer.parseInt(scanner.next());
                        System.out.print(list.get(index));
                        break;
                    case "s":
                        //size()
                        System.out.print(list.size());
                        break;
                    case "e":
                        //isEmpty()
                        System.out.print(list.isEmpty());
                        break;
                    case "r":
                        //remove( Object o )
                        o = scanner.next();
                        list.remove(o);
                        System.out.print(list);
                        break;
                    case "R":
                        //remove( int index )
                        index = Integer.parseInt(scanner.next());
                        list.remove(index);
                        System.out.print(list);
                        break;
                }
                System.out.println("\n------------------");
            }
        }
        scanner.close();
    }
}
