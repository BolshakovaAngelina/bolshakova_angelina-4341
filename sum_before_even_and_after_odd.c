#include <stdio.h>
#include <stdlib.h>
int sum_before_even_and_after_odd(int left, int right, int mass[], int size){
	int sum = 0;
	for (int i = 0; i < left; i++){
		sum += abs(mass[left]);}
	for (; right < size; right ++){
		sum += abs(mass[right]);}
	return sum;
}

