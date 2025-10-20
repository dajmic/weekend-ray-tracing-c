#ifndef INTERVAL_H
#define INTERVAL_H

#include <stdbool.h>

typedef struct {
	double min, max;
} Interval;

Interval interval(double min, double max);
bool surrounds(Interval *i, double x);
double clamp(Interval *i, double x);

#endif
