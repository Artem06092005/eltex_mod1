#pragma once

typedef double (*calc_func)(double, double);

typedef struct {
	const char *name;
	calc_func func;
} Command;

double sum_two(double a, double b);

double sub(double a, double b);

double mul(double a, double b);

double div(double a, double b);

double max2(double a, double b);