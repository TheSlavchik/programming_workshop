#include "integral.h"
#include <math.h>

#define ZERO_ACCURACY -1

double integral(double (*func)(double), double a, double b, int n)
{
    if (n <= 0)
    {
        return ZERO_ACCURACY;
    }

    double step = (b - a) / n;
    double sum = 0.5 * (func(a) + func(b));

    for (int i = 0; i < n; i++)
    {
        double x = a + i * step;
        sum += func(x);
    }

    return sum * step;
}
