#include "equation.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

void test_1()
{
    double a, b, c = 0;
    double accuracy = 1E-7;

    double *res = solve_equation(a, b, c, accuracy);

    assert(res[0] == -1);
    free(res);
}

void test_2()
{
    double a = 1;
    double b = 0;
    double c = -1;
    double accuracy = 1E-7;

    double *res = solve_equation(a, b, c, accuracy);

    assert(res[0] == 2);
    assert(res[1] == -1);
    assert(res[2] == 1);
    free(res);
}

void test_3()
{
    double a = 1;
    double b = 0;
    double c = 0;
    double accuracy = 1E-7;

    double *res = solve_equation(a, b, c, accuracy);

    assert(res[0] == 1);
    assert(res[1] == 0);
    free(res);
}

void test_4()
{
    double a = 1;
    double b = 0;
    double c = 1;
    double accuracy = 1E-7;

    double *res = solve_equation(a, b, c, accuracy);

    assert(res[0] == 0);
    free(res);
}

void test_5()
{
    double a = 1;
    double b = 0;
    double c = -1E-7;
    double accuracy = 1E-7;

    double *res = solve_equation(a, b, c, accuracy);

    assert(res[0] == 2);
    assert(fabs(res[1] + 3E-4) < 1E-4);
    assert(fabs(res[2] - 3E-4) < 1E-4);
    free(res);
}

void test_6()
{
    double a = 1;
    double b = -1E+10;
    double c = -1;
    double accuracy = 1E-7;

    double *res = solve_equation(a, b, c, accuracy);

    assert(res[0] == 2);

    assert(fabs(res[1]) < 1E-11);
    assert(fabs(res[2] - 1E+10) < 1E-11);
    free(res);
}

void test_7()
{
    double a = 1;
    double b = 0;
    double c = -1e-8;
    double accuracy = 1E-7;

    double *res = solve_equation(a, b, c, accuracy);

    assert(res[0] == 1);
    assert(fabs(res[1]) < 1E-7);
    free(res);
}

int main()
{
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    test_6();
    test_7();
}