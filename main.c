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
    const char* operators = "+-*/";
    for(int i = 0; i < strlen(operators); i++)
        if(c == operators[i])
            return true;
    return false;
}

int operatorPrecedence(char operator)
{
    switch (operator)
    {
    case '-': return 0;
    case '+': return 0;
    case '*': return 1;
    case '/': return 1;
    case '^': return 2;    
    
    default:
        printf("%s", "Nonvalid Operator");
    }
    return -1;
}

Associativity operatorAssociativity(char operator)
{
    switch(operator)
    {
        case '+': return LEFT_TO_RIGHT;
        case '-': return LEFT_TO_RIGHT;
        case '*': return LEFT_TO_RIGHT;
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
            postfixExp[postfixIndex++] = c;
        
        else if(isOperator(c))            
        {
            if(isStackEmpty(opStack) || operatorPrecedence(c) > operatorPrecedence(top(opStack)))
            {
                push(opStack, c);
            }
            
            else
            {
                while(!isStackEmpty(opStack) && operatorPrecedence(c) <= operatorPrecedence(top(opStack)))
                {
                    printStack(opStack);
                    if(operatorPrecedence(c) < operatorPrecedence(top(opStack)))
                    {
                        postfixExp[postfixIndex++] = pop(opStack);
                    }  
                    else if (operatorPrecedence(c) == operatorPrecedence(top(opStack)))
                    {
                        printf("%i == %i", operatorPrecedence(c), operatorPrecedence(top(opStack)));
                        if(operatorAssociativity(c) == LEFT_TO_RIGHT)
                            postfixExp[postfixIndex++] = pop(opStack);
                        else if(operatorAssociativity(c) == RIGHT_TO_LEFT)
                        {
                            push(opStack, c);
                            break;
                        }
                    }
                }
            }
            printStack(opStack);
        }        
    }
    while(!isStackEmpty(opStack))
        postfixExp[postfixIndex++] = pop(opStack);
    
    printf("%s\n", postfixExp);
}

int main(int argc, char** argv)
{
    const char* infixExpression = "k+L-M";
    infixToPostfix(infixExpression);
}