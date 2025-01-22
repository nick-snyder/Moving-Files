#include<stdio.h>  
  
long factorial(int n)  
{  
    if (n == 0)  
        return 1;  
    else  
        return(n * factorial(n-1));  
}  
   
void main()  
{  
    int number = 9;  
    printf("%ld\n", factorial(number)); 
}  