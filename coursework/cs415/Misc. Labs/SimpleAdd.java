import java.util.Scanner;

public class SimpleAdd {

    public static void main(String[] args) {

        // initialize variables
        int a;
        int b;
        int sum;

        // initialize Scanner
        Scanner sc;
        sc = new Scanner(System.in);

        a = sc.nextInt();
        b = sc.nextInt();

        // Operation
        sum = a + b;

        // Prints to screen
        System.out.println(sum);
    }
}
