#include "interval.h"

interval init_interval(double min, double max)
{
    interval i;

    i.min = min;
    i.max = max;

    return i;
}

bool surrounds(interval *i, double x)
{
    return i->min < x && x < i->max;
}