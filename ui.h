#ifndef UI_H
#define UI_H
#include "analyze.h"

#define MENU_WIDTH 40
#define TABLE_WIDTH 72
#define RESULT_ROWS 6

// ui_run starts a terminal-based user interface
void ui_run();
void printResult(int size, double *resultArr, int n, algorithm_t a, case_t c);
#endif
