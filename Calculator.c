#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    float data;
    struct Node *link;
} Node;
Node *top=0;
Node *TEMP=0;
char exp2[20];
float calculate (float x, float y, char op)
{

    if (op == '+')
        return (x+y);
    if(op == '-')
        return (x-y);
    if (op == '*')
        return (x*y);
    if (op == '/')
        return (x/y);
    if (op == '^')
        return (pow(x,y));




}

void push(Node **TOP,float x)
{
    Node *n;
    n=(Node *)malloc(sizeof(Node));
    n->data=x;
    n->link=*TOP;
    *TOP=n;
}

void display()
{
    Node *temp=top;
    if(top==0)
    {
        printf("EMPTY LIST!!\n");
        return;
    }
    while(temp!=NULL)
    {
        printf("%f ",temp->data);
        temp=temp->link;
    }
    printf("\n");
}
float peek()
{
    if(top!=NULL)
        return top->data;
}
float  pop(Node **TOP)
{
    if (*TOP != 0)
    {
        Node *temp=*TOP;
        *TOP=(*TOP)->link;
        free(temp);
    }
}
int isempty()
{
    if(top==0)
        return 1;
    else
        return 0;
}
int priority(char x)
{
    if(x=='(')
        return 0;
    if(x=='+' ||x=='-')
        return 1;
    if(x=='*' ||x=='/')
        return 2;
    if(x=='^')
        return 3;
}
void infixtopostfix(char exp[])
{
    char *ptr=exp;

    int flag=0;
    int i=0;
    while(*ptr!='\0')
    {

        int x=0;
        if(isspace(*ptr))
        {
            ptr++;
            continue;
        }
        if(*ptr == ' ')
        {
            ptr+=1;
            continue;

        }
        if(isdigit(*ptr)||(*ptr=='-'&&isdigit(*(ptr+1))))
        {
            if(isdigit(*(ptr+1)))
            {
                x=atoi(ptr);//use atof

                flag=1;
                ptr+=2;

            }

            else
            {
                x=atoi(ptr);
            }
            printf("%i",x);
            exp2[i++]=x;
        }
        else if(*ptr=='(')
        {
            push(&top,*ptr);
        }
        else if(*ptr ==')')
        {
            x=peek();
            while(x!='(')
            {
                printf("%c",x);
                exp2[i++]=x;
                pop(&top);
                x=peek();
            }
        }

        else
        {

            if(top!=0)
            {
                while(priority(top->data)>=priority(*ptr)  )/*  priority of ptr is less than the top it cannot be pushed*/
                {
                    printf("%c",(char)peek());
                    exp2[i++]=peek();
                    pop(&top);
                    if(top==0)
                        break;
                }
                push(&top,*ptr);
            }
            else
                push(&top,*ptr);
        }
        if(flag==0)
            ptr++;

        flag=0;
    }
    ///////////////////////////

    while(top !=0)
    {
        if(peek()!='(')
        {

            char z=pop(&top);
            printf("%c",z);
            exp2[i++]=z;

            z=peek();
            printf("%c",z);
            exp2[i++]=z;
        }


        pop(&top);
    }
}
int main()
{
    /*push(12.0);
    push(123.0);
    push(55.0);
    display();*/
    char exp[20];
    int flag=0;
    char *ptr;
    char x;
    printf("Enter an exp\n");
    gets(exp);
    infixtopostfix(exp);
    while(top!=0)
        pop(&top);
//Printing output
    for(int i=0; i<strlen(exp2); i++)
    {
        if(exp2[i]=='*'||exp2[i]=='-'||exp2[i]=='+'||exp2[i]=='/'||exp2[i]=='^')
        {

            float result,x,y;
            y=(int)peek();
            pop(&top);
            x=(int)peek();
            pop(&top);
            result = calculate (x, y, exp2[i]);
            push(&top,result);
        }
        else
            push(&top,exp2[i]);
    }
    float z=pop(&top);
    printf("\nThe result is %f",z);
    return 0;
}
