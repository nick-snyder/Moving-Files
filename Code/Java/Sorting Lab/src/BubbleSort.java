public class BubbleSort extends Sort{

    public BubbleSort(String fileName) {
        super(fileName);
    }

    public void sort() {

        int n = samples.size();

        while (true) {

            boolean swapped = false;

            for (int i = 1; i < n; i++) {
                if (samples.get(i - 1).measurement < samples.get(i).measurement) {

                    Sample temp = samples.get(i);
                    samples.set(i, samples.get(i - 1));
                    samples.set(i - 1, temp);

                    swapped = true;
                }
            }
            if (!swapped) {
                break;
            }
        }
    }
}
