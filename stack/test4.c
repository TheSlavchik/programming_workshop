#include "stack.h"
#include <assert.h>

void test_1()
{
    Stack *stack = initialize_stack(100);

    push(stack, 13);
    push(stack, 37);

    assert(pop(stack) == 37);
    assert(pop(stack) == 13);
    assert(pop(stack) == -1);

    clear(stack);
}

void test_2()
{
    Stack *stack = initialize_stack(100);

    assert(is_empty(stack) == true);
    assert(is_full(stack) == false);

    for (int i = 0; i < 100; i++)
    {
        push(stack, 13);
    }

    assert(is_empty(stack) == false);
    assert(is_full(stack) == true);

    clear(stack);
}

int main()
{
    test_1();
    test_2();

    return 0;
}