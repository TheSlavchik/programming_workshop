#include "stack.h"
#include <assert.h>
#include <stdio.h>

void test_1()
{
    Stack *stack = initialize_stack();

    push(stack, 13);
    push(stack, 37);

    assert(pop(stack) == 37);
    assert(pop(stack) == 13);
    assert(pop(stack) == -1);
}

void test_2()
{
    Stack *stack = initialize_stack();

    assert(is_empty(stack) == 1);
    assert(is_full(stack) == 0);

    for (int i = 0; i < 100; i++)
    {
        push(stack, 13);
    }

    assert(is_empty(stack) == 0);
    assert(is_full(stack) == 1);
}

int main()
{
    test_1();
    test_2();

    return 0;
}