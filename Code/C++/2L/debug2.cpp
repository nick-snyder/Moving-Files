#include <iostream>
#include <cstdlib>
using namespace std;

int* initArray(int);
int fillArray(int *, int);
int* doubleArray(int *, int);
void displayArray(int *, int);

/* 
 * The program will create an array of given size
 * populate the array with random number from (0-99)
 * and display the array. Next, the program will double
 * the size of the array, repopulate the array and 
 * display it again.
 */


int main(int argc, char ** argv){
    if (argc != 2){
        cout << "wrong number of arguments" << endl;
        exit(1);
    }
    
    int n = atoi(argv[1]); // get size
    srand(time(0));
    
    // create initial array and display it
    int* ptr = initArray(n); //ptr points to array
    fillArray(ptr, n); //array that ptr points to is filled
    displayArray(ptr, n);
    
    // create the double sized array and display it
    doubleArray(ptr, n);
    fillArray(ptr, 2*n);
    displayArray(ptr, 2*n);
    return 0;
}

// Create an array of size n and return its address
int* initArray(int n){
    int arr[n];
    int *ptr = arr;
    return ptr;
}

// Fill array ptr with n random numbers
int fillArray(int *ptr, int n){
    for(int i=0; i<n; i++){
        ptr[i] = rand() % 100;
    }
    return *ptr;
}

// Double the size of the array, make sure no memory leak
int* doubleArray(int *ptr, int n){
    //delete ptr; // (fixed) invalid delete
    int size = 2*n;
    int * tmp = new int[size];
    ptr = tmp;
    delete [] tmp; // (fixed) mismatched free() / delete / delete []
    return ptr;
}

// Display n array elements
void displayArray(int *ptr, int n){
    for(int i=0; i<n; i++){
        cout << ptr[i] << " ";  // (not fixed) Conditional jump or move depends on uninitialised value(s)
    }
    cout << endl;
    
}