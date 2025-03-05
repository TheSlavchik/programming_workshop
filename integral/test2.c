#include "integral.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

double x2(double x)
{
    return x * x;
}

void test_1()
{
    double res = integral(x2, 1, 2, 1000);

    assert(fabs(res - 2.33) < 0.01);
}

void test_2()
{
    double res = integral(sin, 1, 2, 10000);

    assert(fabs(res - 0.956) < 0.001);
}

void test_3()
{
    double res = integral(cos, 1, 2, 10000);

    assert(fabs(res - 0.067) < 0.001);
}

void test_4()
{
    double res = integral(log, 1, 2, 10000);

    assert(fabs(res - 0.386) < 0.001);
}

int main()
{
    test_1();
    test_2();
    test_3();
    test_4();

    return 0;
}