#include "interval.h"

Interval interval(double min, double max)
{
	return (Interval){ .min = min, .max = max };
}

bool surrounds(Interval *i, double x)
{
	return i->min < x && x < i->max;
}

double clamp(Interval *i, double x)
{
	// Clamp value in Interval range.
	if (x < i->min) {
		return i->min;
	}

	if (x > i->max) {
		return i->max;
	}

	return x;
}
