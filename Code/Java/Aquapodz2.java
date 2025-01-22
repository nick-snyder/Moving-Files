import java.util.Scanner;
/**
 *
 *
 * @author Nicholas Snyder
 * @version 15 March 2021
 */
public class Aquapodz2 {
    /**
     *
     *
     * @param args main
     */
    public static void main(String[] args) {
        String command;
        String subcommand;
        double numberOne;
        double numberTwo;
        double numberThree;
        double sum = 0;
        double total = 0;
        double average;
        double max = 0;
        double totalFails = 0;
        double averageFail;
        int a = 0;
        int b = 0;
        int c = 0;
        int f = 0;
        int aFails = 0;
        int bFails = 0;
        int cFails = 0;
        boolean bool = true;
        double[] vendorValuesA = new double[15];
        double[] vendorValuesB = new double[15];
        double[] vendorValuesC = new double[15];
        double[] allFails = new double[15];
        Scanner scanner = new Scanner(System.in);
        while (bool) {
            System.out.println("Please enter a command:");
            command = scanner.nextLine();
            switch (command) {
                case "a", "b", "c" -> {
                    System.out.println("Enter number 1:");
                    numberOne = scanner.nextDouble();
                    System.out.println("Enter number 2:");
                    numberTwo = scanner.nextDouble();
                    System.out.println("Enter number 3:");
                    numberThree = scanner.nextDouble();
                    if (command.equals("a")) {
                        vendorValuesA[a] = numberOne;
                        a++;
                        vendorValuesA[a] = numberTwo;
                        a++;
                        vendorValuesA[a] = numberThree;
                        a++;
                        if ((numberOne < -6.0) || (numberOne > 12.3)) {
                            aFails++;
                            allFails[f] = numberOne;
                            f++;
                        }
                        if ((numberTwo < -6.0) || (numberTwo > 12.3)) {
                            aFails++;
                            allFails[f] = numberTwo;
                            f++;
                        }
                        if ((numberThree < -6.0) || (numberThree > 12.3)) {
                            aFails++;
                            allFails[f] = numberThree;
                            f++;
                        }
                    }
                    if (command.equals("b")) {
                        vendorValuesB[b] = numberOne;
                        b++;
                        vendorValuesB[b] = numberTwo;
                        b++;
                        vendorValuesB[b] = numberThree;
                        b++;
                        if ((numberOne < -6.0) || (numberOne > 12.3)) {
                            bFails++;
                            allFails[f] = numberOne;
                            f++;
                        }
                        if ((numberTwo < -6.0) || (numberTwo > 12.3)) {
                            bFails++;
                            allFails[f] = numberTwo;
                            f++;
                        }
                        if ((numberThree < -6.0) || (numberThree > 12.3)) {
                            bFails++;
                            allFails[f] = numberThree;
                            f++;
                        }
                    }
                    if (command.equals("c")) {
                        vendorValuesC[c] = numberOne;
                        c++;
                        vendorValuesC[c] = numberTwo;
                        c++;
                        vendorValuesC[c] = numberThree;
                        c++;
                        if ((numberOne < -6.0) || (numberOne > 12.3)) {
                            cFails++;
                            allFails[f] = numberOne;
                            f++;
                        }
                        if ((numberTwo < -6.0) || (numberTwo > 12.3)) {
                            cFails++;
                            allFails[f] = numberTwo;
                            f++;
                        }
                        if ((numberThree < -6.0) || (numberThree > 12.3)) {
                            cFails++;
                            allFails[f] = numberThree;
                            f++;
                        }
                    }
                    scanner.nextLine();
                }
                case "A" -> {
                    System.out.println("Enter a subcommand:");
                    subcommand = scanner.nextLine();
                    switch (subcommand) {
                        case "f":
                            System.out.printf("%.2f\n", vendorValuesA[0]);
                            break;
                        case "z":
                            System.out.printf("%.2f\n", vendorValuesA[a - 1]);
                            break;
                        case "a":
                            for (int i = 0; i < a; i++) {
                                System.out.printf("%.2f", vendorValuesA[i]);
                                if (i < a - 1) {
                                    System.out.print(",");
                                } else {
                                    System.out.println();
                                }
                            }
                            break;
                        case "s":
                            for (double v : vendorValuesA) sum += v;
                            System.out.printf("%.3f\n", sum);
                            break;
                        case "v":
                            for (int i = 0; i < a; i++) total += vendorValuesA[i];
                            average = total / a;
                            System.out.printf("%.5f\n", average);
                            break;
                        case "n":
                            System.out.println(a);
                            break;
                        case "m":
                            for (double v : vendorValuesA) if (v > max) max = v;
                            System.out.printf("%.1f\n", max);
                            break;
                        default:
                            System.out.println(subcommand + " is an invalid subcommand.");
                            break;
                    }
                }
                case "B" -> {
                    System.out.println("Enter a subcommand:");
                    subcommand = scanner.nextLine();
                    switch (subcommand) {
                        case "f":
                            System.out.printf("%.2f\n", vendorValuesB[0]);
                            break;
                        case "z":
                            System.out.printf("%.2f\n", vendorValuesB[b - 1]);
                            break;
                        case "a":
                            for (int i = 0; i < b; i++) {
                                System.out.printf("%.2f", vendorValuesB[i]);
                                if (i < b - 1) {
                                    System.out.print(",");
                                } else {
                                    System.out.println();
                                }
                            }
                            break;
                        case "s":
                            for (double v : vendorValuesB) sum += v;
                            System.out.printf("%.3f\n", sum);
                            break;
                        case "v":
                            for (int i = 0; i < b; i++) total += vendorValuesB[i];
                            average = total / b;
                            System.out.printf("%.5f\n", average);
                            break;
                        case "n":
                            System.out.println(b);
                            break;
                        case "m":
                            for (double v : vendorValuesB) if (v > max) max = v;
                            System.out.printf("%.1f\n", max);
                            break;
                        default:
                            System.out.println(subcommand + " is an invalid subcommand.");
                            break;
                    }
                }
                case "C" -> {
                    System.out.println("Enter a subcommand:");
                    subcommand = scanner.nextLine();
                    switch (subcommand) {
                        case "f":
                            System.out.printf("%.2f\n", vendorValuesC[0]);
                            break;
                        case "z":
                            System.out.printf("%.2f\n", vendorValuesC[c - 1]);
                            break;
                        case "a":
                            for (int i = 0; i < c; i++) {
                                System.out.printf("%.2f", vendorValuesC[i]);
                                if (i < c - 1) {
                                    System.out.println(",");
                                } else {
                                    System.out.println();
                                }
                            }
                            break;
                        case "s":
                            for (double v : vendorValuesC) sum += v;
                            System.out.printf("%.3f\n", sum);
                            break;
                        case "v":
                            for (int i = 0; i < c; i++) total += vendorValuesC[i];
                            average = total / c;
                            System.out.printf("%.5f\n", average);
                            break;
                        case "n":
                            System.out.println(c);
                            break;
                        case "m":
                            for (double v : vendorValuesC) if (v > max) max = v;
                            System.out.printf("%.1f\n", max);
                            break;
                        default:
                            System.out.println(subcommand + " is an invalid subcommand.");
                            break;
                    }
                }
                case "n" -> System.out.println(a + b + c);
                case "v" -> {
                    for (int i = 0; i < f; i++) totalFails += allFails[i];
                    averageFail = totalFails / f;
                    System.out.printf("%.3f\n", averageFail);
                }
                case "f" -> {
                    System.out.println("Azuview failures: " + aFails);
                    System.out.println("Bublon  failures: " + bFails);
                    System.out.println("Cryztal failures: " + cFails);
                }
                case "x" -> {
                    System.out.println("Program ended");
                    bool = false;
                }
                default -> System.out.println(command + " is not valid.");
            }
        }
        scanner.close();
    }
}
