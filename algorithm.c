#include "algorithm.h"

//
// Private
//

static void swap(int *arr1, int *arr2){                     //swap function to handle quicksort swaps. 
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
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
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
				swap(&a[j], &a[j + 1]);    //calling swap with addresses of a[j] and address of a[j+1]
				swapped = true;
			}
		}
	if(!swapped)
		break;
	}
}

void insertion_sort(int *a, int n)
{
	for (int i = 1; i < n; ++i){
		int key = a[i];                        
		int j = i - 1;

		while(j >= 0 && a[j] > key) {
			a[j + 1] = a[j];                 //swap
			j = j - 1;
		}
		a[j + 1] = key;
	}	
}


void quick_sort(int *a, int n)
{                                                              
	quick_sort_withHILO(a, 0, (n - 1));	
} 

bool linear_search(const int *a, int n, int v) {
	for (int i = 0; i < n; i++) {
        if (a[i] == v) {
            return true; // Värdet hittat
        }
    }
    return false; // Värdet hittades inte
}

bool binary_search(const int *a, int n, int v) {
	int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2; // Undviker overflow vid stora värden av left och right

        if (a[mid] == v) { // Värdet hittades
            return true; 
        }
        if (a[mid] < v) {
		    left = mid + 1; // Sök i den högra halvan
        } 
		else {
            right = mid - 1; // Sök i den vänstra halvan
        }
    }
    return false; // Värdet hittades inte
}