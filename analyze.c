#include "analyze.h"
#include "algorithm.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 512
//
// Private
//

//
// Public
//
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n) {     
	clock_t start, stop;
	double elapsed;
	int arr[MAX];
    srand(time(NULL));
    
    for (int i = 0; i < MAX; i++) {
        arr[i] = rand() % (50 + 1);
    }
    
    switch (a) {
        case bubble_sort_t:
            break;
        case insertion_sort_t:
            break;
        case quick_sort_t:
            break;
        case binary_search_t:
            break;
        case linear_search_t:
            start = clock();
            binary_search(arr, MAX, arr[0]);
            stop = clock();
        
            elapsed = ((double)(stop - start)) / CLOCKS_PER_SEC;
        
            printf("Total tid: %.8f sekunder\n", elapsed);
            break;
    }
}
