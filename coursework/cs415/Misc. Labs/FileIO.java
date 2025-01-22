import java.io.*;
import java.util.Scanner;

public class FileIO {

    public static void getTokensFromFile (String fileName) throws IOException {

        File f = new File(fileName);
        Scanner s = new Scanner(f);

        while (s.hasNext()) {

            System.out.println(s.next());
        }
    }

    public static void getCharactersFromFile (String fileName) throws IOException {

        File f = new File(fileName);
        BufferedReader reader = new BufferedReader(new FileReader(f));
        int r = 0;


        while (r != -1) {

            r = reader.read();
            char c = (char) r;
            String s = r + " " + c;

            System.out.printf("%5s\n", s);
        }
    }

    public static void getIntsFromFileAndSum (String fileName) throws IOException {

        File f = new File(fileName);
        Scanner s = new Scanner(f);

        int sum = 0;

        while (s.hasNextInt()) {

            int a = s.nextInt();
            sum += a;
            System.out.println(a);
        }

        System.out.println(sum);
    }

    public static void main(String[] args) throws IOException {

        getTokensFromFile("test.txt");
        getCharactersFromFile("test.txt");
        getIntsFromFileAndSum("integers.txt");
    }
}
