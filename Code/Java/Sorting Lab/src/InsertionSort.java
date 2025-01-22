public class InsertionSort extends Sort {

    public InsertionSort(String fileName) {
        super(fileName);
    }

    public void sort() {

        int i = 1;
        int n = samples.size();

        while (i < n) {

            int j = i;

            while (j > 0 && (samples.get(j - 1).measurement < samples.get(j).measurement)) {

                Sample temp = samples.get(j);
                samples.set(j, samples.get(j - 1));
                samples.set(j - 1, temp);
                j--;
            }
            i++;
        }
    }
}
