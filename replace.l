%{
    #include<stdio.h>
%}

%%

"b" fprintf(yyout,"d");
.|\n fprintf(yyout,"%s",yytext);

%%

int yywrap()
{
    return 1;
}

int main(void)
{
    yyin = fopen("input1.txt","r");
    yyout = fopen("output1.txt","w");
    yylex();
    return 0;
}