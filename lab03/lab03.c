#include<stdio.h>
#include<stdlib.h>

/* Main Method */
int main(int args, char** argv) {

    // Read in the Size of the Array.
    int N, i;
    printf("Please enter number of elements in array: ");
    scanf("%d", &N);

    // Statically Allocate Memory for the Array.
//    float arr[N];
    char *arr;
    arr = malloc(N * sizeof(char *));

    // Read in Each Element of the Array
    for (i = 0; i < N; i++) {
        printf("Please enter element %d of array: ", (i + 1));
//        scanf("%s", );
//        char *a = malloc()
//    }

        // Print the Unsorted Array
        printf("Given array is: ");
        printf("[");
        for (i = 0; i < N - 1; i++) {
            printf("%f, ", arr[i]);
        }
        printf("%f]\n", arr[N - 1]);

        // Insertion Sort Algorithm
        float temp;
        int currLoc;
        for (i = 1; i < N; i++) {
            currLoc = i;
            while (currLoc > 0 && arr[currLoc - 1] > arr[currLoc]) {
                temp = arr[currLoc];
                arr[currLoc] = arr[currLoc - 1];
                arr[currLoc - 1] = temp;
                currLoc--;
            }
        }

        // Print the Sorted Array
        printf("Sorted array is: ");
        printf("[");
        for (i = 0; i < N - 1; i++) {
            printf("%f, ", arr[i]);
        }
        printf("%f]\n", arr[N - 1]);

        return 0;
    }
}