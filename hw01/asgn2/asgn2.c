
#include<stdio.h>
#include"asgn2.h"
int main()
{
    // Take user input and then call funtion using the input
    printf("=========Cube Of Odd=========\n");
    int a1;
    printf("Enter an integer for n: ");
    scanf("%d", &a1);  
    cubeOfOdd(a1);
     

    // Take user input and then call funtion using the input
    printf("=========Intro To CS330=========\n");
    int b1;
    printf("Enter an integer for n: ");
    scanf("%d", &b1);  
    introToCS330(b1);


    // Take user input and then call funtion using the input
    printf("=========Print Hello=========\n");
    int c1;
    printf("Enter an integer for n: ");
    scanf("%d", &c1);  
    printHello(c1);

    
    // Take user input and then call funtion using the input
    printf("=========Paint Gallons=========\n");
    float d1,d2,d3;
    printf("Enter an integer for length: ");
    scanf("%f", &d1); 
    printf("Enter an integer for width: ");
    scanf("%f", &d2); 
    printf("Enter an integer for height: ");
    scanf("%f", &d3); 
    printf("%f\n",paintGallons(d1,d2,d3));


    // Take user input and then call funtion using the input
    printf("=========Grader=========\n");
    int e1,e2,e3;
    printf("Enter an integer for avg_exam: ");
    scanf("%d", &e1); 
    printf("Enter an integer for avg_hw: ");
    scanf("%d", &e2); 
    printf("Enter an integer for attendace: ");
    scanf("%d", &e3); 
    grader(e1,e2,e3);

    return 0;
}
