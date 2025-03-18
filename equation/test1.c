#include "equation.h"
#include <assert.h>
#include <math.h>

void test_1()
{
    double a, b, c = 0;
    double eps_a = 1E-5;
    double eps_D = 1E-7;

    double *res = solve_equation(a, b, c, eps_a, eps_D);

    assert(res[0] == -1);
}

void test_2()
{
    double a = 1;
    double b = 0;
    double c = -1;
    double eps_a = 1E-5;
    double eps_D = 1E-7;

    double *res = solve_equation(a, b, c, eps_a, eps_D);

    assert(res[0] == 2);
    assert(res[1] == -1);
    assert(res[2] == 1);
}

void test_3()
{
    double a = 1;
    double b = 0;
    double c = 0;
    double eps_a = 1E-5;
    double eps_D = 1E-7;

    double *res = solve_equation(a, b, c, eps_a, eps_D);

    assert(res[0] == 1);
    assert(res[1] == 0);
}

void test_4()
{
    double a = 1;
    double b = 0;
    double c = 1;
    double eps_a = 1E-5;
    double eps_D = 1E-7;

    double *res = solve_equation(a, b, c, eps_a, eps_D);

    assert(res[0] == 0);
}

void test_5()
{
    double a = 1;
    double b = 0;
    double c = -1E-7;
    double eps_a = 1E-5;
    double eps_D = 1E-7;

    double *res = solve_equation(a, b, c, eps_a, eps_D);

    assert(res[0] == 2);
    assert(fabs(res[1] + 3E-4) < 0.0001);
    assert(fabs(res[2] - 3E-4) < 0.0001);
}

void test_6()
{
    double a = 1;
    double b = -1E+10;
    double c = -1;
    double eps_a = 1E-5;
    double eps_D = 1E-7;

    double *res = solve_equation(a, b, c, eps_a, eps_D);

    assert(res[0] == 2);

    assert(fabs(res[1] + 1E-10) < 1E-9);
    assert(fabs(res[2] - 1E+10) < 1E-9);
}

void test_7()
{
    double a = 1;
    double b = 0;
    double c = -1e-8;
    double eps_a = 1E-5;
    double eps_D = 1E-7;

    double *res = solve_equation(a, b, c, eps_a, eps_D);

    assert(res[0] == 1);

    assert(fabs(res[1]) < 1E-7);
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
