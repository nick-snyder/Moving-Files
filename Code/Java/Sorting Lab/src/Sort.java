import java.io.File;

import java.util.ArrayList;
import java.util.Scanner;

public abstract class Sort {
    ArrayList<Sample> samples = new ArrayList<>();

    public Sort(String fileName) {
        try {
            Scanner s = new Scanner(new File(fileName));
            while (s.hasNextLine()) {
                Scanner line = new Scanner(s.nextLine());
                samples.add(new Sample(line.nextInt(), line.nextDouble()));
            }

        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }

    public String toString() {
        if (samples.size() == 0) {
            return "[]";
        }

        String retVal = "[";
        for (Sample s : samples) {
            retVal += s.toString() + ",";
        }
        return retVal.substring(0, retVal.length() - 1) + "]";
    }
	
    //Sort samples by default in descending order based on
    //measurement.
    public abstract void sort();
}
