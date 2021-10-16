#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* this is my low IQ solution for distinguishing numbers from operators since everything is represented as an integer */

typedef enum
{
    NONE, NUMBER, OPERATOR
} expression;

typedef struct 
{
    int term;
    expression expr;
} entry;

typedef struct
{
    entry* data;
    size_t size;    
    size_t capacity;
} Stack;

const char* exprToStr(expression e) 
{
    switch(e)
    {
        case NONE:     return "NONE";
        case NUMBER:   return "NUMBER";
        case OPERATOR: return "OPERATOR";
    }
}

Stack* createStack(size_t cap)
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->data = (entry*)malloc(sizeof(entry) * cap);
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

int entrycpy(entry* dest, entry* src, size_t size)
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
        entry* temp = (entry*)malloc(sizeof(entry) * s->size);
        entrycpy(temp, s->data, s->size);
        free(s->data);
        s->data = (entry*)malloc(sizeof(entry) * s->capacity);
        entrycpy(s->data, temp, s->size+1);
        free(temp);
        return 1;
    }
    return 0;
}

int push(Stack* stack, entry data)
{      
    if(isStackFull(stack))
        resizeStack(stack);
    stack->data[stack->size] = data;
    stack->size++; 
    return 1;
}

entry pop(Stack* stack)
{
    if(!isStackEmpty(stack))
        return stack->data[--stack->size];
    entry e = {__INT_MAX__, NONE};
    return e;
}

entry top(Stack* s)
{
    return s->data[s->size-1];
}

void printStack(Stack* s)
{
    printf("size: %lu\n", s->size);
    printf("capacity: %lu \n", s->capacity);
    for(int i = 0; i < s->size; i++)
        printf("(%i %s)\n", s->data[i].term, exprToStr(s->data[i].expr));    
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
        stackString[i] = s->data[i].term;
    return stackString;
}