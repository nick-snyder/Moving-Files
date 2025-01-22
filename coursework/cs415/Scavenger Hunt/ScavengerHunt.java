
/**
 * Program shows information about UNH and the CS Dept.
 * 
 * @author Nicholas Snyder
 * @version 15 February 2021
 */

public class ScavengerHunt {

/**
 * Main prints many variables to console in a specific
 * order.
 * 
 * @param args main
 */

    public static void main(String[] args) {
        
        String name = "University of New Hampshire";
        String college = "College of Engineering and Physical Science";
        String deptName = "Computer Science";
        int founded = 1866;
        int deptFounded = 1981;

        System.out.print("Welcome to the [" + name + "]! ");
        System.out.println("UNH was founded in [" + founded + "] and consists of");
        System.out.print("many different schools and colleges. This course, CS415, ");
        System.out.print("is offered by the Department of\n[" + deptName);
        System.out.print("] (founded in [" + deptFounded + "]) which is part of the\n[");
        System.out.println(college + "]. Welcome and enjoy!");
    }
    
}
