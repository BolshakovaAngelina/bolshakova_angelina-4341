#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"
#include <stdio.h>
#include <stdlib.h>
int main(){
	int mass[100];
	int size = 0, flag = -1, m = 0;
	char c;
	do{
		if (flag == -1){
			scanf("%d%c", &m, &c);
			flag = 0;
		}
		else scanf("%d%c", &mass[size++], &c);
	} while (c!='\n');
	switch (m){
		case 0:
			printf("%d\n", index_first_even(mass));
			break;
		case 1:
			printf("%d\n", index_last_odd(mass, size));
			break;
		case 2:
			printf("%d\n", sum_between_even_odd(index_first_even(mass), index_last_odd(mass,size), mass));
			break;
		case 3:
			printf("%d\n", sum_before_even_and_after_odd(index_first_even(mass), index_last_odd(mass, size), mass, size));
			break;
		default:
			puts("Data is not correct\n");
	}
	return 0;
}

