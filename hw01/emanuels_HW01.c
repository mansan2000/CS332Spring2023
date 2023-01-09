#include<stdio.h>
int main()
{
	
/*
Method that takes an integer n and prints out different strings if n is divisible by certain numbers and otherwise it prints the cube of n
Parameters: int n
Return: void
*/
void introToCS330(int n){
    int boolean = 0;
    for (int i = 2; i < n; i++){
        if (n%i==0){
            boolean = 1;
        }
    }
    if (n%3==0 && n%5==0){
        printf("UAB CS 332&532\n");
        return;

    }
    else if (n%5==0){
        printf("UAB\n");
        return;
    }
    else if (n%3==0){
        printf("CS\n");
        return;
    }
    else if (n%7==0){
        printf("UAB\n");
        return;
    }
    else if (boolean==0){
        printf("Go Blazers\n");
        return;
    }
    else{
        int mult = n*n*n;
        printf("%d\n", mult);
        return;
    }
}
    // Take user input and then call funtion using the input
    printf("=========Intro To CS330=========\n");
    int b1;
    printf("Enter an integer for n: ");
    scanf("%d", &b1);  
    introToCS330(b1);
}
