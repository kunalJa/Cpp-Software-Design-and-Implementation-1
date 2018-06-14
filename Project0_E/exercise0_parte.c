#include <stdio.h>
#include <stdlib.h>

int count;
int sum;
int bound;

int isPrime(int num)
{
	if (num <= 1) return 0;
	if (num % 2 == 0 && num > 2) return 0;
	for(int i = 3; i< num / 2; i+= 2)
	{
		if( num % i == 0 ){
			return 0;
		}
	}
	return 1;
}

int findSum()
{
	/*Do something to detect if the number is prime */
	/*Modify the count and sum accordingly*/
	/* Start your code here */
	if (isPrime(count) && count != bound){
	    sum += count;
	}

	count ++;

	if (count >= bound){
		return 0;
	}
	else{
		findSum();
	}
}


int main()
{
	bound = 0;
	count = 0;
	sum = 0;
	printf("Please indicate the boundary of your search: \n");
	scanf("%d", &bound);
	findSum();
	printf("The sum of the prime numbers up to %d is %d\n",bound, sum);
	return 0;
}
