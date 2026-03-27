#include "calc.h"

#include <math.h>

double sum_two(double a, double b) { return a + b; }

double sub(double a, double b) { return a - b; }

double mul(double a, double b) { return a * b; }

double div(double a, double b) {
	if (b == 0) return INFINITY;
	return a / b;
}

double max2(double a, double b) { return (a > b) ? a : b; }