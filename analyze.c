#include "analyze.h"
#include "algorithm.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 512
//
// Private
//
static void makeArraySort(case_t c, int arr[]){
	switch (c){
		case best_t:
			for (int i = 0; i < MAX; i++){
				arr[i] = i;}
		break;
		
		case worst_t:
			for(int i = 0; i < MAX; i++){
				arr[i] = (MAX - i);}
		break;
		
		case average_t:
			for (int i = 0; i < MAX; i++) {
		        arr[i] = rand() % (MAX + 1);}
		break;			
	}
}

/*static void makeArraySearch(case_t c){
	switch (c){
		case best_t
			for (int i = 0; i < MAX; i++){
				arr[i] = i;}
		break;
		case worst_t
			for(int i = 0; i < MAX; i++){
				arr[i] = MAX - i;}
		break;
			} 
	}
	}*/


//
// Public
//
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n) {     
	struct timespec start;
	struct timespec stop;
	int arr[SIZE_START];
    srand(time(NULL));
	
    
 /*  for (int i = 0; i < MAX; i++) {
        arr[i] = rand() % (MAX + 1);
    }*/
//for-loop around switch case for making size * 2 for each iteration
    switch (a) {
        case bubble_sort_t:
			makeArraySort(c,arr);
			bubble_sort(arr,MAX);
			for (int i = 0; i < MAX; i++)
				printf("%d, ", arr[i]);
            break;
        case insertion_sort_t:
			makeArraySort(c,arr);
            break;
        case quick_sort_t:
			makeArraySort(c,arr);
            break;
        case binary_search_t:
			//makeArraySearch(c,arr[]);
            break;
        case linear_search_t:
			//makeArraySearch(c,arr[]);

			//below needs to be put into a private benchmark function, also all printing should be handled in IO.c
            clock_gettime(CLOCK_MONOTONIC, &start);
            binary_search(arr, MAX, arr[0]);
            clock_gettime(CLOCK_MONOTONIC, &stop);

			long elapsed_ns = (stop.tv_sec - start.tv_sec) * 1e9 + (stop.tv_nsec - start.tv_nsec);
		    double elapsed_sec = elapsed_ns / 1e9;

		    printf("\n\nTotal time in nanoseconds: %ld ns\n", elapsed_ns);
		    printf("Total time in scientific notation: %.4e seconds\n", elapsed_sec);
            break;
    }
}
