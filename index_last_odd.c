#include <stdio.h>
int index_last_odd(int mass[], int size){
	for (int i = size - 1; ;i--){
		if (mass[i] % 2 != 0){
			return i;
		}
	}
}
