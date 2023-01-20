#include<stdio.h>

/*
Method that takes an integer array a[] and an int size that represents the length of the array a[]. It then sorts the array a[] using insertionSort.
Parameters: int a[] int size
Return: void
*/
void insertionSort(int a[], int size)
{
	for (int i = 1; i < size; i++)
	{
		int key = *(a + i);
		int j = i - 1;
		while (j >= 0 && key < *(a + j))
		{
			*(a + j + 1) = *(a + j);
			j--;
		}
		*(a + j + 1) = key;
	}
}

/*
Method that takes an integer array a[] and an int size that represents the length of the array a[]. It then prints out the elements in the array to the console.
Parameters: int a[] int size
Return: void
*/
void printArray(int a[], int size)
{
	printf("[");
	for (int i = 0; i < size; i++){
		if(i < size-1){ 
			printf("%d, ", *(a + i));
		}else{
			printf("%d]", *(a + i));
		}
	}
	printf("\n");
}


int main(){
	
    // Take user input and then call funtion using the input
    printf("========= InsertionSort =========\n");
    int n1 = 0;
    printf("Enter an integer for the size of the array: ");
    scanf("%d", &n1);  
	int a[n1];
	int n2;
	int counter = 0;
	while(counter < n1){
		printf("Enter an integer to add to the array: ");
		scanf("%d", &n2);  
		*(a+counter) = n2;
		counter++;
	}
	printArray(a,n1);
	insertionSort(a,n1);
	printArray(a,n1);


}
