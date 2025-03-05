#define MAX_SIZE 100

typedef struct stack
{
    int arr[MAX_SIZE];
    int len;
} Stack;

Stack *initialize_stack();
int is_empty(Stack *stack);
int is_full(Stack *stack);
int push(Stack *stack, int value);
int pop(Stack *stack);