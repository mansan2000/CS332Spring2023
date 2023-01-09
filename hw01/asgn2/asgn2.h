#include<stdio.h>
#include<math.h>
#ifndef __asgn2__
#define __asgn2__


/* the two lines above check to ensure
we haven't already included this header*/
int isPot();
/* your functions go here */
// Note: main() goes in the asgn2.c file


/*
Method that takes in an int n and prints the cube of all odd integers less than n
Parameters: int n
Return: void
*/
void cubeOfOdd(int n){
    for (int i = 0; i < n; i++){
        if (i %2 !=0){
            int result = i*i*i;
            printf("Cube Of Odd Result: %d\n",result);
        }
    }
}


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
    if (n%3==0 && n%7==0){
        printf("UAB CS 330\n");
        return;

    }
    else if (n%7==0){
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

/*
Method that takes an integer n and prints a string with the integers 0 through n with every power of 2 replaced by HELLO
Parameters: int n
Return: void
*/
void printHello(int n){
    for (int i = 0; i <= n; i++){
        if (i==0){
            printf("%d",i);
        }
        else if (isPot(i)==1){
            printf("HELLO");
        }
        else {
            printf("%d",i);
        }
    }
    printf("\n");
    
}


/*
Method that takes in an int x and checks to see if it is a power of two by taking the log of x on base 2 and checking to see if it is an exact number.
If it is an exact number the method returns 1 and otherwise it returns 0.
Parameters: int x
Return: int 1 or 0
*/
int isPot(int x){
    float floorOfNum = (float)(ceil(log(x)/log(2)));
    float ceilOfNum = (float)(floor(log(x)/log(2)));
    if (floorOfNum==ceilOfNum){
        return 1;
    }
    else{
        return 0;
    }
    
}



/*
Method that takes in three floats length, width, and height, and calculates the number of gallons of paint needed to paint the the walls and ceiling of 
the room.
Parameters: floats: length, width, height 
Return: double gallons
*/
double paintGallons(float length, float width, float height){
    double area = (length * height * 2) + (width * height * 2) + length * width;
    double gallons = area/400;
    return ceil(gallons);
}


/*
Method that takes in two floats avg_exams, and avg_hw, and and int attendance, and determines whether they amount to a passing grade or not and prints PASS or FAIL. 
Parameters: floats: avg_exams, avg_hw. 
            int attendance. 
Return: void
*/
void grader(float avg_exams,float avg_hw,int  attendance){
    if (attendance>20 
        && (avg_exams > 70 && avg_hw > 70)
        && (avg_exams > 85 || avg_hw > 85)
        ){
            printf("PASS\n");
        } else {
            printf("FAIL\n");
        }
}



#endif
