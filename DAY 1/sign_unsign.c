#include <stdio.h> 
#include <math.h>
int main() {
	long long int max = (int) (pow(2,63) -1);
	long long int min = (int) (pow(2,63) * -1);
	printf("highest number represented by long long int is %lldln", max);
	printf("Lowest number represented by long long int is %lld\n", min);
	return 0;
}
