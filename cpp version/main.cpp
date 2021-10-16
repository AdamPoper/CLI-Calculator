#include <iostream>
#include <string>
#include "Stack.hpp"

enum Associativity
{
    LEFT_TO_RIGHT, RIGHT_TO_LEFT, NONE
};

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
    const char* operators = "+-*/^";
    for(int i = 0; i < strlen(operators); i++)
        if(c == operators[i])
            return true;
    return false;
}

int operatorPrecedence(char op)
{
    switch (op)
    {
    case '-': return 0;
    case '+': return 0;
    case '*': return 1;
    case '/': return 1;
    case '^': return 2;    
    case '(': return -1;
    case ')': return -1;
    default:
        printf("%s: %c\n", "Nonvalid Operator", op);
    }
    return -1;
}

Associativity operatorAssociativity(char op)
{
    switch(op)
    {
        case '+': return Associativity::LEFT_TO_RIGHT;
        case '-': return Associativity::LEFT_TO_RIGHT;
        case '*': return Associativity::LEFT_TO_RIGHT;
        case '/': return Associativity::LEFT_TO_RIGHT;
        case '^': return Associativity::RIGHT_TO_LEFT;
    }
    return Associativity::NONE;
}

std::string infixToPostfix(const std::string& infixExp)
{
    Stack<std::string> opStack;
    std::string postfixExp;
    int postfixIndex = 0;    
    for(int i = 0; i < infixExp.size(); i++)
    {
        char c = infixExp[i];
        if(isAlphaNumeric(c))
            postfixExp += c;
        
        else if(isOperator(c))            
        {
            if(opStack.isEmpty() || operatorPrecedence(c) > operatorPrecedence((char)opStack.top().c_str()))
                opStack.push();            
            
            else
            {
                while(!isStackEmpty(opStack) && operatorPrecedence(c) <= operatorPrecedence(top(opStack)))
                {
                    if(operatorPrecedence(c) < operatorPrecedence(top(opStack)))
                        postfixExp[postfixIndex++] = pop(opStack);
                      
                    else if (operatorPrecedence(c) == operatorPrecedence(top(opStack)))
                    {                                     
                        if(operatorAssociativity(c) == LEFT_TO_RIGHT)
                            postfixExp[postfixIndex++] = pop(opStack);  

                        else if(operatorAssociativity(c) == RIGHT_TO_LEFT)
                            break;                        
                    }
                }
                push(opStack, c);
            }
        }   
        else if (c == '(' || c == ')')
        {
            if(c == '(')
                push(opStack, c);
            else
            {
                while(top(opStack) != '(')
                    postfixExp[postfixIndex++] = pop(opStack);
                pop(opStack); // pop (
            }
        }      
        //printResults(c, opStack, postfixExp);     
    }
    while(!isStackEmpty(opStack))
        postfixExp[postfixIndex++] = pop(opStack);
    
    //printf("%s\n", postfixExp);
    deleteStack(opStack);
    return postfixExp;
}

float evaluatePostfixExpression(const std::string& postfixExp)
{
    Stack* evalStack = createStack(5);
    for(int i = 0; i < strlen(postfixExp); i++)
    {
        char c = postfixExp[i];
        if(isAlphaNumeric(c))
            push(evalStack, c-'0');
        else if (isOperator(c))
        {
            int op1 = pop(evalStack);
            int op2 = pop(evalStack);            
            switch(c)
            {
                case '*': 
                {
                    int result = op1 * op2;
                    printf("%i %c %i = %i\n", op1, c, op2, result);
                    push(evalStack, result);
                    printStack(evalStack);
                }
                break;
                case '+':    
                {
                    int result = op1 + op2;
                    printf("%i %c %i = %i\n", op1, c, op2, result);
                    push(evalStack, result);
                }                
                break;
                case '-':   
                {
                    int result = op2 - op1;
                    printf("%i %c %i = %i\n", op2, c, op1, result);
                    push(evalStack, result);
                }                 
                break;
                case '/':  
                {
                    int result = op2 / op1;
                    printf("%i %c %i = %i\n", op2, c, op1, result);
                    push(evalStack, result);
                }                  
                break;
                case '^': 
                {
                    int result = pow(op2, op1);
                    printf("%i %c %i = %i\n", op2, c, op1, result);
                    push(evalStack, result);
                }                  
                break;
                default:
                    printf("%s", "Non-valid operator");
            }
        }
    }
    int result = pop(evalStack);
    deleteStack(evalStack);
    return result;
}

int main() 
{
    std::string if1 = "k+L-M*N+(O^P)*W/U/V*T+Q";;
    std::string if2 = "3*(9+(7^2))/2";
    std::string postFixExp = infixToPostfix(if1);
}