#include "integral.h"
#include <assert.h>
#include <math.h>

void test_1()
{
    double (*func)(double) = sin;
    double a = 1;
    double b = 2;
    double n = 10000;

    double res = integral(func, a, b, n);

    assert(fabs(res - 0.956) < 0.001);
}

void test_2()
{
    double (*func)(double) = cos;
    double a = 1;
    double b = 2;
    double n = 10000;

    double res = integral(func, a, b, n);

    assert(fabs(res - 0.067) < 0.001);
}

void test_3()
{
    double (*func)(double) = log;
    double a = 1;
    double b = 2;
    double n = 10000;

    double res = integral(func, a, b, n);

    assert(fabs(res - 0.386) < 0.001);
}

void test_4()
{
    double (*func)(double) = log;
    double a = 1;
    double b = 2;
    double n = 0;

    double res = integral(func, a, b, n);

    assert(fabs(res + 1) < 1E-7);
}

int main()
{
    test_1();
    test_2();
    test_3();
    test_4();

    return 0;
}
