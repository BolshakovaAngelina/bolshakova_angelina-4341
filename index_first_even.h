#include <stdio.h>
int index_first_even(int mass[]){
	for (int i = 0; ; i++){
		if (mass[i] % 2 == 0){
			return i;
		}
	}
}
	
