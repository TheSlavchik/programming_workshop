#include <stdbool.h>

#define STACK_IS_FULL -1
#define STACK_IS_EMPTY -2

typedef struct stack
{
    int *arr;
    int max_length;
    int len;
} Stack;

Stack *initialize_stack(int max_length);
bool is_empty(Stack *stack);
bool is_full(Stack *stack);
int push(Stack *stack, int value);
int pop(Stack *stack, int *element);
void clear(Stack *stack);
