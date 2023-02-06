%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int flag = 0;
%}

%token NUMBER;

%left '+' '-'

%left '/' '*' '%'

%left '(' ')'

%%

arithmeticExpression: E{
    if(flag == 0)
        printf("\nResult = %d",$$);
    return 0;
};
E: E'+'E {$$=$1+$3;}
|E'-'E {$$=$1-$3;}
|E'*'E {$$=$1*$3;}
|E'%'E {$$=$1%$3;}
|E'/'E {$$=$1/$3;}
|'('E')' {$$=$2;}
|NUMBER {$$=$1;}
;

%%

int main()
{
    printf("\nEnter the arithmetic expression: ");
    yyparse();
    if(flag == 0)
        printf("\nArithmetic Expression is valid.");
}

int yyerror()
{
    printf("\nArithmetic Expression is invalid");
    flag = 1;
    exit(0);
}
