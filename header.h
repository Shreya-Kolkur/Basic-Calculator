#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

typedef struct node{
    int data;
    struct node *next,*before;
}node;

typedef node* number;

void init(number *n);
void add_term(number *n,int m);
void display(number n);
number addition(number n1,number n2);
number subtraction(number n1,number n2);
number multiplication(number n1,number n2);
number division(number n1,number n2);
void add_before(number *n,int m);
number mod(number n1,number n2);
number power(number n1,number n2);

typedef struct stackoperand{
    number *a;
    int size1;
    int top1;
}stackoperand;

typedef struct stackoperator{
    char *b;
    int size2;
    int top2;
}stackoperator;

void init_stackoperator(stackoperator *s2, int len);
void init_stackoperand(stackoperand *s1,int len);
void pushoperand(stackoperand *s1, number n1);
void pushoperator(stackoperator *s2,char c);
int isFulloperand(stackoperand s1) ;
int isEmptyoperand(stackoperand s1);
int isFulloperator(stackoperator s2);
int isEmptyoperator(stackoperator s2);
char popoperator(stackoperator *s2);
number popoperand(stackoperand *s1);
char peekoperator(stackoperator s2);
number peekoperand(stackoperand s1);


#endif // HEADER_H_INCLUDED
