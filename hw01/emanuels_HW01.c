#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
Method that takes an integer n and prints out different strings if n is divisible by certain numbers and otherwise it prints the cube of n
Parameters: int n
Return: void
*/
void introToCS332532(int n){

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
int UABNumber(int n2){
	int total = 0;
    for (int i = 1; i < n2; i++){
        if (n2%i==0){
			total += i;
        }
    }
	printf("Total: %d\n",total);
	if(total == n2){
		printf("True\n");
	} else{
		printf("False\n");
	}


	
	return 1;

}
int reverseNumber(int n3){
	int result = 0;

	while (n3 != 0){
		int x = n3%10;
		result = result * 10 + x;	
		n3 /= 10;
	}

	return result;
}


int smallerThanIndex(){
    // int numbers[arraySize];
    int counter = 0;
    int numbers[] = {10,20,1,2,30};
    int arraySize = sizeof(numbers)/sizeof(*(numbers));

    for (int i = 0; i < arraySize; i++){
        if (*(numbers+i) < i){
            counter++;
            // printf("%d",numbers[i]);
        }
    }
    // printf("%d",counter);
    return counter;
}

int arrayDetails(){
    int numbers[] = {-8, -23, 18, 103, 0, 1, -4, 631, 3, -41, 5};
    int arraySize = sizeof(numbers)/sizeof(*(numbers));
    printf("%d", arraySize);

        for (int i = 0; i < arraySize; i++){
        if (*(numbers+i) < i){
            
        }
    }

    int result[] = {arraySize};

    return 0;

}


int main()
{
	


    // // Take user input and then call funtion using the input
    // printf("=========Intro To CS332532=========\n");
    // int n;
    // printf("Enter an integer for n: ");
    // scanf("%d", &n);  
    // introToCS332532(n);

	
	
    // // Take user input and then call funtion using the input
    // printf("========= UABNumber =========\n");
    // int n2;
    // printf("Enter an integer for n2: ");
    // scanf("%d", &n2);  
	// UABNumber(n2);



    // // Take user input and then call funtion using the input
    // printf("========= reverseNumber =========\n");
    // int n3;
    // printf("Enter an integer for n3: ");
    // scanf("%d",&n3);  
	// printf("%d",reverseNumber(n3));


    // // Take user input and then call funtion using the input
    // printf("========= smallerThanIndex =========\n");
    // // int n4;
    // // printf("Enter an integer for n4: ");
    // // scanf("%d",&n4);  
	// printf("%d",smallerThanIndex());
    arrayDetails();
}

