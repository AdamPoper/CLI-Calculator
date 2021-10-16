#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int* data;
    size_t size;    
    size_t capacity;
} Stack;

Stack* createStack(size_t cap)
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->data = (int*)malloc(sizeof(int) * cap);
    s->size = 0;
    s->capacity = cap;
    return s;
}

int isStackFull(Stack* s)
{
    return (s->size == s->capacity);
}

int isStackEmpty(Stack* s)
{
    return (s->size == 0);
}

int intcpy(int* dest, int* src, size_t size)
{
    if(!dest || !src)
        return 0;
    for(int i = 0; i < size; i++)
        dest[i] = src[i];    
    return 1;
}

int resizeStack(Stack* s)
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
        return 1;
    }
    return 0;
}

int push(Stack* stack, int data)
{      
    if(isStackFull(stack))
        resizeStack(stack);
    stack->data[stack->size] = data;
    stack->size++; 
    return 1;
}

int pop(Stack* stack)
{
    if(!isStackEmpty(stack))
        return stack->data[--stack->size];
    return __INT_MAX__;
}

int top(Stack* s)
{
    return s->data[s->size-1];
}

void printStack(Stack* s)
{
    printf("size: %lu\n", s->size);
    printf("capacity: %lu \n", s->capacity);
    for(int i = 0; i < s->size; i++)
        printf("%i ", s->data[i]);    
    printf("\n");
}

void deleteStack(Stack* s)
{
    free(s->data);
    free(s);
}

char* stackString(Stack* s)
{
    char* stackString = (char*)malloc(sizeof(char) * s->size);
    for(int i = 0; i < s->size; i++)
        stackString[i] = s->data[i];
    return stackString;
}