import java.util.ArrayList;
import java.util.Arrays;

public class Multiples {

    private int[] result;
    private ArrayList<Integer> numbers;

    public Multiples(ArrayList<Integer> numbers) {
        this.numbers = numbers;
        this.result = new int[numbers.size()];
    }

    // HELPER METHODS GO HERE

    public boolean isMultiple(int num, int div) {

        // if num is a multiple of div
        return num % div == 0;
    }

    public void assignValue(int n, int i) {
        int value = getNumbers().get(i);
        result[n] = value;
        getNumbers().remove(i);
    }

    public void unassignValue(int n) {

        // value at index n
        int value = getResult()[n];

        // add value to numbers at index 0
        getNumbers().add(0, value);

        // assign 0 to index n in result
        getResult()[n] = 0;
    }

    /**
     * DO NOT CHANGE!
     * Method to begin solving the problem for the first index in results.
     *
     * @return True if solution was found, false if none was possible.
     */
    public boolean solve() {
        return solve(0);
    }

    /**
     * Recursive method to solve the problem from a given index onward. Assumes
     * that any index before n was already assigned a valid value.
     *
     * @param n The current index in the results array to find a value for.
     * @return True if solution was found, false if none was possible from this index.
     */
    private boolean solve(int n) {

        // problem is solved. Base case
        if (n >= result.length) {
            return true;
        } else {
            for (int i = 0; i < numbers.size(); i++) {

                // if valid
                if (isMultiple(numbers.get(i), n + 1)) {

                    // assign that value at index n
                    //result[n] = (int) number;
                    assignValue(n, i);

                    // recursively call the method to solve the rest of the problem
                    // and store output to boolean variable
                    boolean bool = solve(n + 1);

                    // if the recursive call returned true
                    if (bool) {
                        return true;
                    } else {

                        // un-assign the value at n. Backtracking
                        unassignValue(n);

                    }
                }
            }

        }

        // no solution found
        return false;

    }

    public int[] getResult() {
        return result;
    }

    public ArrayList<Integer> getNumbers() {
        return numbers;
    }


    public static void main(String[] args) {
        Integer[] numbers;
        Multiples m;

        //FIRST TEST (SOLUTION POSSIBLE WITHOUT BACKTRACKING)
        numbers = new Integer[]{1, 6, 21, 40, 25};
        m = new Multiples(new ArrayList<Integer>(Arrays.asList(numbers)));

        if (m.solve()) {
            System.out.println("Found solution for " + Arrays.toString(numbers));
        }
        else {
            System.out.println("No solution possible!");
        }
        System.out.println(Arrays.toString(m.getResult()));
        System.out.println();

        //SECOND TEST (SOLUTION POSSIBLE WITH BACKTRACKING)
        numbers = new Integer[]{15, 10, 6, 12, 16};
        m = new Multiples(new ArrayList<Integer>(Arrays.asList(numbers)));

        if (m.solve()) {
            System.out.println("Found solution for " + Arrays.toString(numbers));
        }
        else {
            System.out.println("No solution possible!");
        }
        System.out.println(Arrays.toString(m.getResult()));
        System.out.println();

        //THIRD TEST (NO SOLUTION)
        numbers = new Integer[]{15, 10, 6, 12, 17};
        m = new Multiples(new ArrayList<Integer>(Arrays.asList(numbers)));

        if (m.solve()) {
            System.out.println("Found solution for " + Arrays.toString(numbers));
        }
        else {
            System.out.println("No solution possible!");
        }
        System.out.println(Arrays.toString(m.getResult()));
    }

}

