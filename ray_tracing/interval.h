#ifndef INTERVAL_H
#define INTERVAL_H

#include <stdbool.h>

typedef struct
{
    double min, max;
} interval;

interval init_interval(double min, double max);
bool surrounds(interval *i, double x);
double clamp(interval *i, double x);

#endif