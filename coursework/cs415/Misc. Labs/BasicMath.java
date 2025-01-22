import java.util.Scanner;

/**
 * 
 * 
 * @author Nicholas Snyder
 * @version 8 April 2021
 */

public class BasicMath {

    /**
     * 
     * 
     * @param args      main
     */

    public static void main(String[] args) {

        int a;
        int b;

        String operator = "";
        //String operator1 = "";
        Scanner scanner = new Scanner(System.in);

        a = scanner.nextInt();
        b = scanner.nextInt();

        /*
            // when input is void or too long           // when input is not the correct symbol
        while ( (operator.length() != 1) || !(operator.equals("+") || operator.equals("-") || operator.equals("*") || operator.equals("/") || operator.equals(">")) ) {
            
            operator = scanner.nextLine();
        }
        if (operator.equals("/")) {
            operator1 = "\\";
        }
        */

        operator = scanner.nextLine();

        System.out.print(a + " " + operator + " " + b + " = " + evaluateExpression(a, b, operator));    
        
        scanner.close();
    }

    /**
     * 
     * 
     * @param a         int
     * @param b         int
     * @param operator  String
     * @return          String
     */

    public static String evaluateExpression(int a, int b, String operator) {
        
        int expression;

        switch (operator) {
            case "+":

                expression = a + b;
                break;
        
            case "-":

                expression = a - b;
                break;

            case "*":

                expression = a * b;
                break;

            case "\\":

                expression = a / b;
                break;

            case ">":

                if (a > b) {
                    expression = 1;
                } else {
                    expression = 0;
                }
                break;

            default:

                expression = 2;
                break;
        }
        
        if (operator.equals(">")) {
            if (expression == 1) {
                return "true";
            } else {
                return "false";
            }
        }
        return Integer.toString(expression);
    }
}
