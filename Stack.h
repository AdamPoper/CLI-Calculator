#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { false, true } bool;

typedef struct
{
    int* data;
    size_t size;    
    size_t capacity;
} Stack;

typedef Stack stack_t;

stack_t* createStack(size_t cap)
{
    stack_t* s = (stack_t*)malloc(sizeof(stack_t));
    s->data = (int*)malloc(sizeof(int) * cap);
    s->size = 0;
    s->capacity = cap;
    return s;
}

bool isStackFull(stack_t* s)
{
    return (s->size == s->capacity);
}

bool isStackEmpty(stack_t* s)
{
    return (s->size == 0);
}

bool intcpy(int* dest, int* src, size_t size)
{
    if(!dest || !src)
        return false;
    for(int i = 0; i < size; i++)
        dest[i] = src[i];    
    return true;
}

bool resizeStack(stack_t* s)
{
    if(isStackFull(s))
    {
        s->capacity *= 2;
        int* temp = (int*)malloc(sizeof(int) * s->size);
        intcpy(temp, s->data, s->size);
        free(s->data);
        s->data = (int*)malloc(sizeof(int) * s->capacity);
        intcpy(s->data, temp, s->size+1);
        free(temp);
        return true;
    }
    return false;
}

bool push(stack_t* stack, int data)
{      
    if(isStackFull(stack))
        resizeStack(stack);
    stack->data[stack->size] = data;
    stack->size++; 
    return true;
}

int pop(stack_t* stack)
{
    if(!isStackEmpty(stack))
        return stack->data[--stack->size];
    return __INT_MAX__;
}

int top(stack_t* s)
{
    return s->data[s->size-1];
}

void printStack(stack_t* s)
{
    printf("size: %lu\n", s->size);
    printf("capacity: %lu \n", s->capacity);
    for(int i = 0; i < s->size; i++)
        printf("%i ", s->data[i]);    
    printf("\n");
}