#include <stdio.h>
#include "Stack.h"

typedef enum 
{
    LEFT_TO_RIGHT, RIGHT_TO_LEFT
} Associativity;

bool isAlphaNumeric(char c)
{
    const char* nonAlphaNumerics = "`~!@#$%^&*()_-+=?/';:{[}]\\,<.>\"";
    for(int i = 0; i < strlen(nonAlphaNumerics); i++)
        if(c == nonAlphaNumerics[i])
            return false;    
    return true;
}

bool isOperator(char c)
{
    const char* operators = "+-x/";
    for(int i = 0; i < strlen(operators); i++)
        if(c == operators[i])
            return false;
    return true;
}

int operatorPrecedence(char operator)
{
    switch (operator)
    {
    case '-': return 0;
    case '+': return 0;
    case 'x': return 1;
    case '/': return 1;
    case '^': return 2;    
    
    default:
        printf("%s", "Nonvalid Operator");
    }
}

Associativity operatorAssociativity(char operator)
{
    switch(operator)
    {
        case '+': return LEFT_TO_RIGHT;
        case '-': return LEFT_TO_RIGHT;
        case 'x': return LEFT_TO_RIGHT;
        case '/': return LEFT_TO_RIGHT;
        case '^': return RIGHT_TO_LEFT;
    }
}

const char* infixToPostfix(const char* infixExp)
{
    Stack* opStack = createStack(5);
    char postfixExp[64];
    int postfixIndex = 0;    
    for(int i = 0; i < strlen(infixExp); i++)
    {
        char c = infixExp[i];
        if(isAlphaNumeric(c))
        {
            postfixExp[postfixIndex] = c;
            postfixIndex++;
        }
        else if(isOperator(c))            
        {
            if(operatorPrecedence(c) > operatorPrecedence(top(opStack)))
            {
                push(opStack, c);
            }
            // TODO make sure this is right
            else
            {
                while(!isStackEmpty(opStack) && operatorPrecedence(c) <= operatorPrecedence(top(opStack)))
                {
                    if(operatorPrecedence(c) < operatorPrecedence(top(opStack)))
                    {
                        postfixExp[postfixIndex++] = pop(opStack);
                    }    
                    else if(operatorPrecedence(c) == operatorPrecedence(top(opStack)))
                    {
                        if(operatorAssociativity(c) == LEFT_TO_RIGHT)
                        {
                            postfixExp[postfixIndex++] = pop(opStack);
                        }
                        else if(operatorAssociativity(c) == RIGHT_TO_LEFT)
                        {
                            push(opStack, c);
                        }
                    }
                }
            }
        }
    }
}

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