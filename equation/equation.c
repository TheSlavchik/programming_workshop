#include "equation.h"
#include <math.h>
#include <stdlib.h>

int solve_equation(double a, double b, double c, double eps, double **res)
{
    double D, x1, x2;

    if (fabs(a) < eps)
    {
        return A_EQUALS_ZERO;
    }

    D = pow(b, 2) - 4 * a * c;

    if (fabs(D) < eps)
    {
        D = 0;
    }

    if (D < 0)
    {
        return NO_ROOTS;
    }
    else if (D == 0)
    {
        x1 = -b / (2 * a);

        *res = malloc(sizeof(double));

        (*res)[0] = x1;

        return ONE_ROOT;
    }
    else
    {
        *res = malloc(sizeof(double) * 2);

        double q = -0.5 * (b + copysign(sqrt(D), b));
        x1 = q / a;
        x2 = c / q;

        if (x2 > x1)
        {
            (*res)[0] = x1;
            (*res)[1] = x2;
        }
        else
        {
            (*res)[0] = x2;
            (*res)[1] = x1;
        }

        return TWO_ROOTS;
    }
}
