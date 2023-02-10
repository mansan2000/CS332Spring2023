#include<stdio.h>


int isPrime(int givenNumber){
	int total = 0;
    for (int i = 1; i < givenNumber; i++){
        if (givenNumber%i==0){
			total += i;
        }
    }
	printf("Total: %d\n",total);
	if(total == 1){
		printf("The given number is a prime\n");
	} else{
		printf("The given number is not a prime\n");
	}
	return 1;

}


int main(){
	
//    // Take user input and then call funtion using the input
//    printf("========= UABNumber =========\a");
//    int n2;
//    printf("Enter an integer for givenNumber: ");
//    scanf("%d", &n2);
//	isPrime(n2);

char d = '3';
int x = 3;
    printf("%d",x+d);
}
