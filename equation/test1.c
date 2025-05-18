#include "equation.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void zero_a_test()
{
    double a, b, c = 0;
    double eps = 1E-7;
    double *res;

    assert(solve_equation(a, b, c, eps, &res) == A_EQUALS_ZERO);
}

void two_roots_test()
{
    double a = 1;
    double b = 0;
    double c = -1;
    double eps = 1E-7;
    double *res;

    assert(solve_equation(a, b, c, eps, &res) == TWO_ROOTS);
    assert(res[0] == -1);
    assert(res[1] == 1);
    free(res);
}

void one_root_test()
{
    double a = 1;
    double b = 0;
    double c = 0;
    double eps = 1E-7;
    double *res;

    assert(solve_equation(a, b, c, eps, &res) == ONE_ROOT);
    assert(res[0] == 0);
    free(res);
}

void no_roots_test()
{
    double a = 1;
    double b = 0;
    double c = 1;
    double eps = 1E-7;
    double *res;

    assert(solve_equation(a, b, c, eps, &res) == NO_ROOTS);
}

void eps_test1()
{
    double a = 1;
    double b = 0;
    double c = -1E-7;
    double eps = 1E-7;
    double *res = NULL;

    assert(solve_equation(a, b, c, eps, &res) == TWO_ROOTS);
    assert(fabs(res[0] + 3E-4) < 0.0001);
    assert(fabs(res[1] - 3E-4) < 0.0001);
    free(res);
}

void eps_test2()
{
    double a = 1;
    double b = -1E+10;
    double c = -1;
    double eps = 1E-7;
    double *res;

    assert(solve_equation(a, b, c, eps, &res) == TWO_ROOTS);
    assert(fabs(res[0] + 1E-10) < 1E-11);
    assert(fabs(res[1] - 1E+10) < 1E-11);
    free(res);
}

void eps_test3()
{
    double a = 1;
    double b = 0;
    double c = -1e-8;
    double eps = 1E-7;
    double *res;

    assert(solve_equation(a, b, c, eps, &res) == ONE_ROOT);
    assert(fabs(res[0]) < 1E-7);
    free(res);
}

int main()
{
    zero_a_test();
    two_roots_test();
    one_root_test();
    no_roots_test();
    eps_test1();
    eps_test2();
    eps_test3();
}
