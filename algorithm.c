#include "algorithm.h"

//
// Private
//
static void bubble_swap(int* adrp1, int* adrp2) {
	int temp = *adrp1;
	*adrp1 = *adrp2;
	*adrp2 = temp;
}
static void quick_swap(int *arr1, int *arr2){               //swap function to handle quicksort swaps. 
	int temp = *arr1;                                       //temp is an int because it only needs to hold the value of arr1 at pos 0
	*arr1 = *arr2;
	*arr2 = temp;
}
static int quick_partition(int arr[], int low, int high){
	int pivot = arr[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++){
		if(arr[j] < pivot){
			i++;
			quick_swap(&arr[i], &arr[j]);
		}
	}
	quick_swap(&arr[i + 1], &arr[high]);
	return i + 1;
}
static void quick_sort_withHILO(int *a, int low, int high) {        //soloution for not getting to include high and low for quicksort call
    if (low < high) {
        int pi = quick_partition(a, low, high);

        quick_sort_withHILO(a, low, pi - 1);   // Recursive call on the left of pivot
        quick_sort_withHILO(a, pi + 1, high);  // Recursive call on the right of pivot
    }
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




void quick_sort(int *a, int n)
{                                                              
	quick_sort_withHILO(a, 0, n - 1);	
} 

bool linear_search(const int *a, int n, int v)
{
	return false; // TODO: linear search
}

bool binary_search(const int *a, int n, int v)
{
	return false; // TODO: binary search
}
