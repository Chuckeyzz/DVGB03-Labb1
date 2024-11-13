#include "algorithm.h"

//
// Private
//
static void bubble_swap(int* adrp1, int* adrp2) {
	int temp = *adrp1;
	*adrp1 = *adrp2;
	*adrp2 = temp;
}


//
// Public
//

void bubble_sort(int *a, int n)     //bublesort working
{
	bool swapped = false;
	for(int i = 0; i < (n - 1); i++){
		swapped = false;
		for (int j = 0; j < (n - i - 1); j++){
			if(a[j] > a[j + 1]){
				bubble_swap(&a[j], &a[j + 1]);    //calling swap with addresses of a[j] and address of a[j+1]
				swapped = true;
			}
		}
	if(!swapped)
		break;
	}
}

void insertion_sort(int *a, int n)
{
	// TODO: insertion sort
}



void quick_sort(int *a, int n){                              //a is an array inparameter
	
}   

bool linear_search(const int *a, int n, int v)
{
	return false; // TODO: linear search
}

bool binary_search(const int *a, int n, int v)
{
	return false; // TODO: binary search
}
