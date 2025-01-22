// [nxn]*[nx1]=[nx1] (Ax=y) matrix-vector multiplication
class MatrixMultiplication
{
    static void Main(string[] args)
    {
        int size = 2;

        // print out A
        System.Console.Write("A:\n  ");
        double[,] A = new double[,] { { 0.3, 0.1 }, 
                                      { -0.4, 0.2 } };
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                System.Console.Write(A[i, j] + " ");
            }
            System.Console.Write("\n  ");
        }
        System.Console.WriteLine();

        // print out x
        System.Console.Write("x:\n  ");
        double[] x = new double[]{ 0.5, 5};
        for (int i = 0; i < size; i++)
        {
            System.Console.Write(x[i] + "\n  ");
        }
        System.Console.WriteLine();

        // evaluate and assing values to b
        double[] y = new double[size];
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                y[i] += A[i, j] * x[j];
            }
        }

        // print out b
        System.Console.Write("b:\n  ");
        for (int i = 0; i < size; i++)
        {
            System.Console.Write(y[i] + "\n  ");
        }


        /*
        [AB]ij = sum from k=1 to n of aik * bkj

        for (int i = 0; i < n; i++)
        {

        }
        */
    }
}
    