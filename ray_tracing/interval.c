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

double clamp(interval *i, double x)
{
    // Clamp value in interval range.
    if (x < i->min)
    {
        return i->min;
    }

    if (x > i->max)
    {
        return i->max;
    }

    return x;
}