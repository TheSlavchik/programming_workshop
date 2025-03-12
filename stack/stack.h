#include <stdbool.h>

typedef struct stack
{
    int *arr;
    int max_length;
    int len;
    bool is_empty;
} Stack;

Stack *initialize_stack(int max_length);
bool is_empty(Stack *stack);
bool is_full(Stack *stack);
int push(Stack *stack, int value);
int pop(Stack *stack);
void clear(Stack * stack);