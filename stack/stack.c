#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack *initialize_stack()
{
    Stack *stack = malloc(sizeof(Stack));
    stack->len = 0;
    return stack;
}

int is_empty(Stack *stack)
{
    if (stack->len == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int is_full(Stack *stack)
{
    if (stack->len == MAX_SIZE)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int push(Stack *stack, int value)
{
    if (is_full(stack) == 1)
    {
        return -1;
    }

    stack->arr[stack->len] = value;
    stack->len++;
    return 0;
}

int pop(Stack *stack)
{
    if (is_empty(stack))
    {
        return -1;
    }

    int element = stack->arr[stack->len - 1];
    stack->len--;

    return element;
}