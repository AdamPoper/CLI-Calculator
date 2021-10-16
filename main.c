#include <math.h>
#include <ctype.h>

#include "Stack.h"

typedef enum 
{
    LEFT_TO_RIGHT, RIGHT_TO_LEFT
} Associativity;

int isOperator(char c)
{
    const char* operators = "+-*/^";
    for(int i = 0; i < strlen(operators); i++)
        if(c == operators[i])
            return 1;
    return 0;
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
    case '(': return -1;
    case ')': return -1;
    default:
        printf("%s: %c\n", "Invalid Operator", operator);
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
        default:  return -1;
    }
}

void printResults(char input, Stack* opStack, const char* pfExp)
{
    char* stackStr = stackString(opStack);
    printf("%c   %s   %s\n", input, stackStr, pfExp);
    free(stackStr);
}

Stack* infixToPostfix(const char* infixExp)
{
    Stack* opStack = createStack(5);
    Stack* postFixStack = createStack(10);
    char num[16];
    for(int i = 0; i < strlen(infixExp); i++)
    {
        int j = 0;
        char c = infixExp[i];
        while(isdigit(c))
        {
            num[j++] = c;
            i++;
            c = infixExp[i];
        }
        num[j] = '\0';
        if(strlen(num))
        {
            //printf("num %s\n", num);
            int n = atoi(num);
            entry e = {n, NUMBER};
            //printf("Pushing %d\n", n);
            push(postFixStack, e);
            //printStack(postFixStack);
        }
        if(isOperator(c))            
        {
            entry e = {c, OPERATOR};
            if(isStackEmpty(opStack) || operatorPrecedence(c) > operatorPrecedence(top(opStack).term))
                push(opStack, e);                                   
            else
            {
                while(!isStackEmpty(opStack) && operatorPrecedence(c) <= operatorPrecedence(top(opStack).term))
                {
                    if(operatorPrecedence(c) < operatorPrecedence(top(opStack).term))
                        push(postFixStack, pop(opStack));
                      
                    else if (operatorPrecedence(c) == operatorPrecedence(top(opStack).term))
                    {                                     
                        if(operatorAssociativity(c) == LEFT_TO_RIGHT)
                            push(postFixStack, pop(opStack));
                        else if(operatorAssociativity(c) == RIGHT_TO_LEFT)
                            break;                        
                    }
                }
                push(opStack, e);
            }
        }   
        else if (c == '(' || c == ')')
        {
            entry e = {c, OPERATOR};
            if(c == '(')
                push(opStack, e);
            else
            {
                while(top(opStack).term != '(')
                    push(postFixStack, pop(opStack));
                pop(opStack); // pop (
            }
        }      
    }
    while(!isStackEmpty(opStack))
        push(postFixStack, pop(opStack));
    
    deleteStack(opStack);
    return postFixStack;
}

int evaluatePostfixExpression(Stack* postfixExp)
{
    Stack* evalStack = createStack(5);
    for(int i = 0; i < postfixExp->size; i++)
    {
        entry e = postfixExp->data[i];
        //printf("c: %d\n", e.term);  
        // here is how it distinguishes from numbers and operators
        // for example the number 43 maps to + the program would get confused whether to use 43 as an operator or as a number      
        if(e.expr == NUMBER)
        {
            //printf("pushing %d\n", e.term);
            push(evalStack, e);
        }
        else if (e.expr == OPERATOR)
        {
            entry op1 = pop(evalStack);
            entry op2 = pop(evalStack);    
            switch(e.term)
            {
                case '*': 
                {
                    int result = op1.term * op2.term;
                    //printf("%i %c %i = %i\n", op1, c, op2, result);
                    entry r = {result, NUMBER};
                    push(evalStack, r);
                }
                break;
                case '+':    
                {
                    int result = op1.term + op2.term;
                    //printf("%i %c %i = %i\n", op1, e.term, op2, result);
                    entry r = {result, NUMBER};
                    push(evalStack, r);
                }                
                break;
                case '-':   
                {
                    int result = op2.term - op1.term;
                    //printf("%i %c %i = %i\n", op2, c, op1, result);
                    entry r = {result, NUMBER};
                    push(evalStack, r);
                }                 
                break;
                case '/':  
                {
                    int result = op2.term / op1.term;
                    //printf("%i %c %i = %i\n", op2, c, op1, result);
                    entry r = {result, NUMBER};
                    push(evalStack, r);
                }                  
                break;
                case '^': 
                {
                    int result = pow(op2.term, op1.term);
                    //printf("%i %c %i = %i\n", op2, c, op1, result);
                    entry r = {result, NUMBER};
                    push(evalStack, r);
                }                  
                break;
                default:
                    printf("%s", "Invalid Operator");
            }
        }
    }
    entry result = pop(evalStack);
    deleteStack(evalStack);
    return result.term;
}

int main(int argc, char** argv)
{    
    char infixExpression[128];
    scanf("%s", infixExpression);
    Stack* postFixStack = infixToPostfix(infixExpression);
    //printStack(postFixStack);
    int result = evaluatePostfixExpression(postFixStack);
    printf("%i\n", result);
    free(postFixStack);
    return 0;
}