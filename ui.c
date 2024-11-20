#include "ui.h"
#include "io.h"
#include "analyze.h"


#include <stdbool.h>
#include <stdio.h>

//
// Private
//

static void ui_invalid_input()
{
	printf("info> bad input\n");
}

static void ui_exit()
{
	printf("info> bye\n");
}

static char ui_get_choice()
{
	char buf[3];

	printf("input> ");
	return read_line(buf, 3) ? buf[0] : 0;
}

static void ui_line(char c, int n)
{
	while (n-- > 0) {
		putchar(c);
	}
	putchar('\n');
}

static void ui_menu_options(const char *options[], int num_options)
{
	int i;

	for (i=0; i<num_options; i++) {
		printf("    %c) %s\n", 'a'+i, options[i]);
	}
}

static void ui_menu()
{
	const char *options[] = {
		"Menu",
		"Exit\n",
		
		"Bubble sort best case",
		"Bubble sort worst case",
		"Bubble sort average case\n",
		"Insertion sort best case",
		"Insertion sort worst case",
		"Insertion sort average case\n",
		"Quick sort best case",
		"Quick sort worst case",
		"Quick sort average case\n",
		"Linear search best case",
		"Linear search worst case",
		"Linear search average case\n",
		"Binary search best case",
		"Binary search worst case",
		"Binary search average case\n",
	};

	ui_line('=', MENU_WIDTH);
	ui_menu_options(options, sizeof(options) / sizeof(char *));
	ui_line('-', MENU_WIDTH);
}
static void printTable(char currAlgo[]){
	printf("************************************************************************\n");
	printf("                        %s                                              \n", currAlgo);
	printf("------------------------------------------------------------------------\n");
	
}
//this function prints only the time for the last element executed beacuse of the forloop, need to callfrom inside the for-loop in analyze.c
//
// Public
//

void printResult(int size, double *resultArr, int n){
	//double time = resultBuf->time;
	printf("************************************************************************\n");
	printf("------------------------------------------------------------------------\n");
	printf("size        time T(s)        time T(s)        time T(s)        time T(s)\n");
	printf("------------------------------------------------------------------------\n");
	for (int i = 0; i < n + 1; i++){
		//funct for printing table
		if(i != 0){
			printf("%-5d       %.8f\n", size, resultArr[i]);
			size = size * 2;
		}
	}
	
}

void ui_run()
{
	bool running, show_menu;
	result_t result[RESULT_ROWS];

	show_menu = true;
	running = true;
	while (running) {
		if (show_menu) {
			show_menu = false;
			ui_menu();
		}
		switch (ui_get_choice()) {
			// House keeping
			case 'a':
				show_menu = true;
				break;
			case 'b':
				running = false;
				break;
			
			// Bubble sort
			case 'c':
				printTable("Buble Sort : Best Case");
				benchmark(bubble_sort_t, best_t, result, RESULT_ROWS);    //create already sorted array for ... a[i] = i
				break;
			case 'd':
				printTable("Buble Sort : Worst Case");
				benchmark(bubble_sort_t, worst_t, result, RESULT_ROWS);   //create as unsorted array as possible
				break;
			case 'e':
				printTable("Buble Sort : Average Case");
				benchmark(bubble_sort_t, average_t, result, RESULT_ROWS);   //create randomised array
				break;
			
			//insertion sort
			case 'f':
				printTable("Insertion Sort : Best Case");
				benchmark(insertion_sort_t, best_t, result, RESULT_ROWS);    //create already sorted array for ... a[i] = i
				break;
			case 'g':
				printTable("Insertion Sort : Worst Case");
				benchmark(insertion_sort_t, worst_t, result, RESULT_ROWS);   //create as unsorted array as possible
				break;
			case 'h':
				printTable("Insertion Sort : Average Case");
				benchmark(insertion_sort_t, average_t, result, RESULT_ROWS);   //create randomised array
				break;
			
			//quick sort
			case 'i':
				printTable("Quick Sort : Best Case");
				benchmark(quick_sort_t, best_t, result, RESULT_ROWS);    //create already sorted array for ... a[i] = 
				break;
			case 'j':
				printTable("Quick Sort : Worst Case");
				benchmark(quick_sort_t, worst_t, result, RESULT_ROWS);   //create as unsorted array as possible
				break;
			case 'k':
				printTable("Quick Sort : Average Case");
				benchmark(quick_sort_t, average_t, result, RESULT_ROWS);   //create randomised array
				break;
			
			//linear search
			case 'l':
				printTable("Linear Search : Best Case");
				benchmark(linear_search_t, best_t, result, RESULT_ROWS);    //create array where we're looking for the first search-position
				break;
			case 'm':
				printTable("Linear Search : Worst Case");
				benchmark(linear_search_t, worst_t, result, RESULT_ROWS);   //create array where we're looking for the last possible search
				break;
			case 'n':
				printTable("Linear Search : Average Case");
				benchmark(linear_search_t, average_t, result, RESULT_ROWS);   //create randomised array
				break;	
			
			//binary search
			case 'o':
				printTable("Binary Search : Best Case");
				benchmark(binary_search_t, best_t, result, RESULT_ROWS);    //create array where we're looking for the first search-position
				break;
			case 'p':
				printTable("Binary Search : Worst Case");
				benchmark(binary_search_t, worst_t, result, RESULT_ROWS);   //create array where we're looking for the last possible search
			break;
			case 'q':
				printTable("Binary Search : Average Case");
				benchmark(binary_search_t, average_t, result, RESULT_ROWS);   //create randomised array
				break;	
			
			// Invalid input
			default:
				show_menu = false;
				ui_invalid_input();
				break;
		}
	}
	ui_exit();
}
