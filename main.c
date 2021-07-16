#include <stdio.h>
#include "Stack.h"

int main(int argc, char** argv)
{
    Stack* stack = createStack(10);
    for(int i = 0; i < 18; i++)
        push(stack, i);
    printStack(stack);
    printf("%i\n", pop(stack));
    printStack(stack);
    for(int i = 0; i < 10; i++)
        pop(stack);
    printStack(stack);
    for(int i = 3; i < 16; i+=2)
        push(stack, i);
    printStack(stack);        
}