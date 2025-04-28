#include "stack.h"
#include <assert.h>
#include <stdlib.h>

void stack_pop_test()
{
    Stack *stack = initialize_stack(100);

    push(stack, 13);
    push(stack, 37);

    int *element1 = malloc(sizeof(int));
    int *element2 = malloc(sizeof(int));
    int *element3 = malloc(sizeof(int));

    pop(stack, element1);
    pop(stack, element2);
    pop(stack, element3);

    assert(element1[0] == 37);
    assert(element2[0] == 13);
    assert(pop(stack, element3) == STACK_IS_EMPTY);

    clear(stack);
}

void stack_overflow_test()
{
    Stack *stack = initialize_stack(10);

    assert(is_empty(stack) == true);
    assert(is_full(stack) == false);

    for (int i = 0; i < 10; i++)
    {
        push(stack, 13);
    }

    assert(push(stack, 13) == STACK_IS_FULL);
    assert(is_empty(stack) == false);
    assert(is_full(stack) == true);

    clear(stack);
}

int main()
{
    stack_pop_test();
    stack_overflow_test();

    return 0;
}
