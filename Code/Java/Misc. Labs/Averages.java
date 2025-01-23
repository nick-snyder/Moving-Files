import java.util.Scanner;

/**
 * Program finds a student's final grade based
 * upon the grades of previous assignments.
 * 
 * @author Nicholas Snyder
 * @version 16 February 2021
 */

public class Averages {

    /**
     * Main first declares weights of each grade as constants
     * and then declares all the other variables and scanner.
     * Next, main asks user to input all of the grades and 
     * stores them to the corresponding variable of a similar 
     * name. Each category of grade is averaged together and
     * stored in a variable. Lastly, the final grade is 
     * calculated by multiplying each average with its weight 
     * and is printed to the console. Printf is used to format 
     * each grade correctly.
     * 
     * @param args main
     */

    public static void main(String[] args) {
        
        // Weights
        final double PARTICIPATION = 0.15;
        final double TESTS = 0.45;
        final double PROJECTS = 0.40;

        // Declarations
        double gradeParticipation;
        double gradeTestOne;
        double gradeTestTwo;
        double gradeTestThree;
        double averageTestGrade;
        double gradeProjectOne;
        double gradeProjectTwo;
        double averageProjectGrade;
        double gradeFinal;
        Scanner scnr = new Scanner(System.in);

        // Participation
        System.out.println("Enter student's participation grade.");
        gradeParticipation = scnr.nextDouble();

        // Tests
        System.out.println("Enter student's first test grade.");
        gradeTestOne = scnr.nextDouble();

        System.out.println("Enter student's second test grade.");
        gradeTestTwo = scnr.nextDouble();

        System.out.println("Enter student's third test grade.");
        gradeTestThree = scnr.nextDouble();

        averageTestGrade = (gradeTestOne + gradeTestTwo + gradeTestThree) / 3;
        System.out.printf("Test average: " + "%.2f\n", averageTestGrade);

        // Projects
        System.out.println("Enter student's first project grade.");
        gradeProjectOne = scnr.nextDouble();

        System.out.println("Enter student's second project grade.");
        gradeProjectTwo = scnr.nextDouble();

        averageProjectGrade = (gradeProjectOne + gradeProjectTwo) / 2;
        System.out.printf("Project average: " + "%.2f\n", averageProjectGrade);

        // Final
        gradeFinal = (gradeParticipation * PARTICIPATION) 
            + (averageTestGrade * TESTS) + (averageProjectGrade * PROJECTS);
        System.out.printf("Student grade: " + "%.2f\n", gradeFinal);
    }
}
