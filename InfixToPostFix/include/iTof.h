#ifndef __IFNTO__$_
#define __IFNTO__$_ 1234
#include<stack.h>
#include<queue.h>
int isOperator(char c);
int isOperand(char c);
int getPrecedence(char op);
void appendToPostfix(char c,char *pf,int *terminatorIndex);
Stack *convertInfixToPostfixSingleDigit(char *exp);
Stack *convertInfixToPostfixMultiDigit(char *exp);
void appendOperatorToPostfix(Queue *queue,char op);
void appendNumberToPostfix(Queue *queue,int number);
#endif
