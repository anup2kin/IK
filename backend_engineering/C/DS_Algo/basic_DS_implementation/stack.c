#include <stdio.h>
#include <stdlib.h>

typedef struct Stack{
    int *buf;
    int top;
    int capacity;
} Stack;

void init_stack(Stack *stk, int size){
    stk->buf = (int *) malloc (sizeof(int) * size);
    stk->top = -1;
    stk->capacity = size;
}

void push(Stack *stk, int value){
    if(stk->top == stk->capacity - 1){
        int *temp = (int *) realloc(stk->buf, stk->capacity * 2);
        if(temp == NULL){
            printf("Memory allocation failed!");
            return;
        }

        stk->buf = temp;
        stk->capacity *= 2;
    }

    ++stk->top;
    stk->buf[stk->top] = value;
}

int pop(Stack *stk, int *isEmpty){
    *isEmpty = 0;

    if(stk->top == -1){
        *isEmpty = 1;
        return -1;
    }

    int poppedValue = stk->buf[stk->top];
    --stk->top;

    return poppedValue;
}

void free_stack(Stack *stk){
    free(stk->buf);
    stk->buf = NULL;
    stk->top = -1;
    stk->capacity = 0;
}

int main() {
    Stack myStack;
    init_stack(&myStack, 2); // Initial capacity of 2

    push(&myStack, 10);
    push(&myStack, 20);
    push(&myStack, 30); // Capacity will be doubled here

    int isEmpty;
    int poppedValue;

    while (1) {
        poppedValue = pop(&myStack, &isEmpty);
        if (isEmpty) {
            break;
        }
        printf("%d ", poppedValue);
    }
    printf("\n");

    free_stack(&myStack);

    return 0;
}