#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

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
	int boolean;
    for (int i = 1; i < n2; i++){
        if (n2%i==0){
			total += i;
        }
    }
	if(total == n2){
		boolean = 1;
	} else{
		boolean = 0;
	}


	
	return boolean;

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


int smallerThanIndex(int numbers[], int arraySize){
    // int numbers[arraySize];
    int counter = 0;
//    int arraySize = sizeof(numbers)/sizeof(*(numbers));

    for (int i = 0; i < arraySize; i++){
        if (*(numbers+i) < i){
            counter++;
            // printf("%d",numbers[i]);
        }
    }
    // printf("%d",counter);
    return counter;
}

float *arrayDetails(int numbers1[], int sizeOfArray){
//    int numbers[] = {-8, -23, 18, 103, 0, 1, -4, 631, 3, -41, 5};
//    int arraySize = sizeof(numbers)/sizeof(*(numbers));

	int *numbers = numbers1;
	int arraySize = sizeOfArray;
//    printf("arraySize %d\n", arraySize);

	int minimumValue = *(numbers)+1;
	int indexMinimumValue = -1;
	int maximumValue = *(numbers)-1;
	int indexMaximumValue = -1;
	double totalValueOfElements = 0;
	for (int i = 0; i < arraySize; i++){
		totalValueOfElements += *(numbers+i); 

//		printf("numbers[i] %d\n", *(numbers+i));
//		printf("maximumValue %d\n", maximumValue);
		if (*(numbers+i) > maximumValue){
			maximumValue = *(numbers+i); 
			indexMaximumValue = i;
		}
		if (*(numbers+i) < minimumValue){
			minimumValue = *(numbers+i); 
			indexMinimumValue = i;
		}
	}
//    printf("minimumValue %d\n", minimumValue);
//    printf("indexMinimumValue %d\n", indexMinimumValue);
//    printf("mean %0.2f\n", totalValueOfElements/arraySize);
//    printf("maximumValue %d\n", maximumValue);
//    printf("indexMaximumValue %d\n", indexMaximumValue);

	

	float *array;
	array = malloc(6 * sizeof(float));
	*(array) = arraySize;
	*(array+1) = minimumValue;
	*(array+2) = indexMinimumValue;
	*(array+3) = totalValueOfElements/arraySize;
	*(array+4) = maximumValue;
	*(array+5) = indexMaximumValue;

    return array;

}

/*
Method that takes a float array a[] and an int size that represents the length of the array a[]. It then prints out the elements in the array to the console.
Parameters: int a[] float size
Return: void
*/
void printFloatArray(float a[], int size)
{

	printf("[");
	for (int i = 0; i < size; i++){
		if(i < size-1){ 
			printf("%0.02f,",  *(a + i));
		}else{
			printf("%0.02f]",  *(a + i));
		}
	}
	printf("\n");
}
/*
Method that takes an integer array a[] and an int size that represents the length of the array a[]. It then prints out the elements in the array to the console.
Parameters: int a[] int size
Return: void
*/
void printIntArray(int a[], int size)
{
	printf("[");
	for (int i = 0; i < size; i++){
		if(i < size-1){ 
			printf("%d,", *(a + i));
		}else{
			printf("%d]", *(a + i));
		}
	}
	printf("\n");
}

int main()
{
     // Take user input and then call funtion using the input
     printf("=========Intro To CS332532=========\n");
     int n;
     printf("Enter an integer for n: ");
     scanf("%d", &n);
     introToCS332532(n);


     // Take user input and then call funtion using the input
     printf("========= UABNumber =========\n");
     int n2;
     printf("Enter an integer for n2: ");
     scanf("%d", &n2);
    printf("Boolean: %d\n", UABNumber(n2));



     // Take user input and then call funtion using the input
     printf("========= reverseNumber =========\n");
     int n3;
     printf("Enter an integer for n3: ");
     scanf("%d",&n3);
	 printf("%d\n",reverseNumber(n3));


     // Take user input and then call funtion using the input
     printf("========= smallerThanIndex =========\n");
	 int numbers[] = {10,20,1,2,30};
    printf("[");
    for (int i = 0; i < 5; i++) {
        printf("%d,",*(numbers + i));
    }
    printf("]\n");
    printf("Numbers smaller than: %d\n",smallerThanIndex(numbers, sizeof(numbers)/sizeof(*(numbers))));


    printf("========= arrayDetails =========\n");
    int numbers1[] = {-8, -23, 18, 103, 0, 1, -4, 631, 3, -41, 5};
    printf("Input Array: ");
	printIntArray(numbers1,11);
	float *ptr = arrayDetails(numbers1,11);
    printf("Returned Array: ");
	printFloatArray(ptr,6);
}

