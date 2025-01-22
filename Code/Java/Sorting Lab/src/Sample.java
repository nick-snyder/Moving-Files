/**
 * Created by matt on 11/13/17.
 */
public class Sample {
    public int id;
    public double measurement;

    public Sample(int id, double measurement) {
        this.id = id;
        this.measurement = measurement;
    }

    public String toString() {
        return String.format("<%d,%.2f>", id, measurement);
    }
}
