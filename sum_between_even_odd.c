#include <stdio.h>
#include <stdlib.h>
#include "sum_between_even_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"
int sum_between_even_odd(int left, int right, int mass[]){
	int sum = 0;
	for (;left < right; left++){
		sum += abs(mass[left]);
	}
	return sum;
}
		
