#include "analyze.h"
#include "algorithm.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//
// Private
//
static void makeArraySort(case_t c, int arr[],int size){

	switch (c){
		case best_t:
			for (int i = 0; i < size; i++){
				arr[i] = i;}
		break;
		
		case worst_t:
			for(int i = 0; i < size; i++){
				arr[i] = (size - i);}
		break;
		
		case average_t:
			for (int i = 0; i < size; i++) {
		        arr[i] = rand() % (size + 1);}
		break;			
	}
}

static void quick_best_case(int arr[], int low, int high, int *current_value) {
	if (low > high) {
		return;
	}
	int mid = (low + high) / 2;
	arr[mid] = (*current_value)++;
	quick_best_case(arr, low, mid - 1, current_value);
	quick_best_case(arr, mid + 1, high, current_value);
}

static void ArrSortQuick(case_t c, int arr[], int size){
	switch (c){
		case best_t:
			int currValue = 1;
			quick_best_case(arr, 0, size - 1, &currValue);
		break;
		
		case worst_t:                         //worst case ok
			for (int i = 0; i < size; i++){
				arr[i] = size - i;}
		break;
		
		case average_t:
			for (int i = 0; i < size; i++){
				arr[i] = rand() % (size);}
		break;		
	}
}


static void makeArraySearch(algorithm_t a,case_t c, int arr[],int size) {
	switch (c) {
		case best_t:
			for (int i = 0; i < size; i++) {               //iterates through the array, filling all positions with 1
				arr[i] = 1;
			}	
		break;
		case worst_t:
			for(int i = 0; i < size; i++) {              //filling array with zeroes looking for 1
				arr[i] = 0;                              //search for 1
				}						
		break;
		
		case average_t:
			if(a == binary_search_t){
				for (int i = 0; i < size; i++){
					if(i == (size / 4)) {
						arr[i] = 1;
					}
					else {
						arr[i] = 0;
					}
				}
			}
		else{                     //linear search
			for(int i = 0; i < size; i++){
				if(i == size / 2){
					arr[i] = 1;
				}
				else {
					arr[i] = 0;
				}
			}
		}
		break;
	}
}

//
// Public
//
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n) {   //n is the constant RESULTROWS (= 6)   
	struct timespec start;                        //struct for start of time keeping
	struct timespec stop;                         //struct for end of time keeping
    srand(time(NULL));                            //seed for random, using time
	int size = SIZE_START;                        //size variable to be muliplied by 2 each iteration of switch case below
	int orgSize = SIZE_START;
	int *arr = (int *)malloc(size * sizeof(int));
	double timeArr[n];

	
	for (int i = 0; i < n + 1; i++){                                    //repeating loop 6 + 1 times. + 1 is for warming up CPU 
																		//first value of each algorithm is bloated due to caching
	    switch (a) {
	        case bubble_sort_t:
				makeArraySort(c,arr,size);
				clock_gettime(CLOCK_MONOTONIC, &start);
				bubble_sort(arr,size);
				clock_gettime(CLOCK_MONOTONIC, &stop);
	            break;
			
	        case insertion_sort_t:
				makeArraySort(c,arr,size);
				clock_gettime(CLOCK_MONOTONIC, &start);
				insertion_sort(arr,size);
				clock_gettime(CLOCK_MONOTONIC, &stop);
	            break;
			
	        case quick_sort_t:
				ArrSortQuick(c,arr,size);
				clock_gettime(CLOCK_MONOTONIC, &start);
	            quick_sort(arr, size);
	            clock_gettime(CLOCK_MONOTONIC, &stop);
	            break;
			
	        case binary_search_t:
				makeArraySearch(a,c,arr,size);
				clock_gettime(CLOCK_MONOTONIC, &start);
	            binary_search(arr, size, 1);
	            clock_gettime(CLOCK_MONOTONIC, &stop);
	            break;
			
	        case linear_search_t:
				makeArraySearch(a,c,arr,size);           
	            clock_gettime(CLOCK_MONOTONIC, &start);
	            linear_search(arr, size, 1);
	            clock_gettime(CLOCK_MONOTONIC, &stop);
	
	            break;
		}
		double elapsed_sec = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) / 1000000000.0;
		buf->time = elapsed_sec;
		buf->size = size;
		timeArr[i] = elapsed_sec;

		//make FUNCT for calculating time and printing in UI.c with buf as inparameter
		//****************SEE ARRAY_LIST.C FROM LECTURE FOR DYNAMIC CALCULATION OF TIMES************************
		if(i != 0){
			//printf("%d        %.12f \n", size, elapsed_sec);
			size = size * 2;                    //mutiplying size by 2 for next value
		}

		//reallocating memory for new size of array
		int *new_arr = (int *)realloc(arr, size * sizeof(int));
        if (new_arr == NULL) { // Check if memory reallocation succeeded
            fprintf(stderr, "Memory reallocation failed\n");
            free(arr);         // Free previously allocated memory
            return;
        }
        arr = new_arr;         // Update the pointer to the newly allocated memory
	}
	printResult(orgSize,timeArr,n);
	free(arr);
}