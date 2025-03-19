#include "stack.h"
#include <stdlib.h>

Stack *initialize_stack(int max_length)
{
    Stack *stack = malloc(sizeof(Stack));
    stack->arr = malloc(sizeof(int) * max_length);
    stack->max_length = max_length;
    stack->len = 0;
    stack->is_empty = true;
    return stack;
}

bool is_empty(Stack *stack)
{
    return stack->is_empty;
}

bool is_full(Stack *stack)
{
    return stack->len == stack->max_length;
}

int push(Stack *stack, int value)
{
    if (is_full(stack))
    {
        return STACK_IS_FULL;
    }

    stack->arr[stack->len] = value;
    stack->len++;

    stack->is_empty = false;

    return 0;
}

int pop(Stack *stack)
{
    if (is_empty(stack))
    {
        return STACK_IS_EMPTY;
    }

    int element = stack->arr[stack->len - 1];
    stack->len--;

    if (stack->len == 0)
    {
        stack->is_empty = true;
    }

    return element;
}

void clear(Stack *stack)
{
    free(stack->arr);
    free(stack);
}
