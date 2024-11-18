#include "analyze.h"
#include "algorithm.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 512
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
/*static void ArrSortQuick(case_t c, int arr[]){}*/
//make cases for quick sort

//creat an array for the different cases for search algos
static void makeArraySearch(algorithm_t a, case_t c, int arr[],int size) {
	if(a == linear_search_t) {	     //for linear search
		switch (c) {
			case best_t:
				for (int i = 0; i < size; i++) {               //iterates through the array, filling the position 0 with a 1, and the rest with 0
					if(i == 0){
						arr[i] = 1;
					}
					else{
					arr[i] = 0;
					}
			}
			break;
			case worst_t:
				for(int i = 0; i < size; i++) {               //iterates through the array, filling the position 511 with a 1, and the rest with 0
					arr[i] = 0;                              //seraches for 1, not existing
				}				
			
			break;
			case average_t:
				for(int i = 0; i < size; i++){
					if(i == size / 2){
						arr[i] = 1;
					}
					else {
						arr[i] = 0;
					}
				}
			break;
		}
	}
	else{	                //for binary search
		switch (c) {
			case best_t:
				for (int i = 0; i < size; i++) {               //iterates through the array, filling all positions with 1
					arr[i] = 1;
				}	
			break;
			case worst_t:
				for(int i = 0; i < size; i++) {               //iterates through the array, filling the position 511 with a 1, and the rest with 0
					arr[i] = 0;                              //search for 1
					}						
			break;
			case average_t:
				for(int i = 0; i < size; i++){
					if(i == size / 2){
						arr[i] = 1;
					}
					else {
						arr[i] = 0;
					}
				}
			break;
		}
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
	int *arr = (int *)malloc(size * sizeof(int));
	
	for (int i = 0; i < n + 1; i++){                                    //repeating loop 6 times
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
				makeArraySort(c,arr,size);
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
		//make FUNCT for calculating time and printing in UI.c with buf as inparameter
		if(i != 0){
			printf("Total time in seconds: %.12f seconds\n", elapsed_sec);
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
	free(arr);
}

