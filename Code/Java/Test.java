//import javax.sound.midi.Soundbank;

//import java.util.Scanner;

/**
 * testing java
 * 
 * @author Nicholas Snyder
 * @version 19 February 2021
 */

public class Test {

    /**
     * 
     * 
     * @param args main
     */

    public static double rainfall(int[] arr) {
        int total = 0;
        int sum = 0;
        for (int i = 0; i < arr.length; i++ ) {
            if (arr[i] == -99) {
                // Stop
                //System.out.println("index " + arr[i]);
                i = arr.length;
                if (total != 0) {
                    total--;
                }
            }
            else if (arr[i] < 0) {
                // Skip over
                total--;
                //System.out.println("index " + arr[i]);
            } else {
                // Add
                sum += arr[i];
                total++;
                //System.out.println("sum " + sum);
            }
        }
        if (total == 0) {
            total = 1;
        }
        double average = sum / (total);
        return average;
    }

    public static void main(String[] args) {
        int[] arr = { 2, -20, 8, -99 } ;
        System.out.println(rainfall(arr));
    }
}
