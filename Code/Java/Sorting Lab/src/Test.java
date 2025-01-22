public class Test {
    public static void main(String[] args) {
        InsertionSort sort = new InsertionSort("dat.csv");
        sort.sort();
        System.out.println(sort);
    }
}
