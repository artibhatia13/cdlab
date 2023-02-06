#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int isKeyword(char buffer[])
{
    char keywords[32][10] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float",
    "for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union", 
    "unsigned","void","volatile","while"};

    for(int i = 0; i < 32; ++i)
    {
        if(strcmp(keywords[i], buffer) == 0)
        {
            return 1;
        }
    }
    return 0;
    
}
    
int main() 
{
    int j = 0;
    char c, buffer[31], operators[] = "+-*/%=<>!&|", separators[]=",;{}()";
    FILE *fp;
    fp = fopen("input.txt","r");
    if(fp == NULL)
    {
        printf("Error while opening the file\n");
        exit(0);
    }

    while((c = fgetc(fp)) != EOF) 
    {
        
        if(c == '/')
        {
            char t = c;
            c = fgetc(fp);
            if(c == '/')
            {
                while(c != '\n')
                    c = fgetc(fp);
        
                continue;
            }
            else
            {
                ungetc(c,fp);
                c = t;
            }
        }

        for(int i = 0; i < 12; ++i)
        {
            if(c == operators[i])
            {
                if(c == '+')
                {
                    c = fgetc(fp);
                    if(c == '+')
                        printf("++ is Increment operator\n");
                    else
                    {
                        ungetc(c,fp);
                        printf("+ is Addition operator\n");
                    }
                }
                    
                else if(c == '-')
                {
                    c = fgetc(fp);
                    if(c == '-')
                        printf("-- is Decrement operator\n");
                    else
                    {
                        ungetc(c,fp);
                        printf("- is Subtraction operator\n");
                    }
                }                    
                else if(c == '*')
                    printf("%c is Mutiplication operator\n", c);
                else if(c == '/')
                    printf("%c is Division operator\n", c);
                else if(c == '%')
                    printf("%c is Modulus operator\n", c);
                else if(c == '=')
                {
                    c = fgetc(fp);
                    if(c == '=')
                        printf("== is Relational operator\n");
                    else
                    {
                        ungetc(c,fp);
                        printf("= is Assignment operator\n", c);
                    }
                }

                else if(c == '!')
                {
                    c = fgetc(fp);
                    if(c == '=')
                        printf("!= is Relational operator\n");
                    else
                        printf("! is logical operator");
                }

                else if((c == '<') || (c == '>'))
                {
                    char t = c;
                    c = fgetc(fp);
                    if(c == '=')
                        printf("%c%c is Relational operator\n", t,c);
                    else
                    {
                        ungetc(c,fp);
                        printf("%c is Relational operator\n", t);
                    }
                }

                else if(c == '&' || c== '|')
                {
                    char t = c;
                    c = fgetc(fp);
                    if(c == t)
                        printf("%c%c is Logical operator\n", t,c);
                    else
                        ungetc(c,fp);
                }
                    
            }
        }

        for(int i = 0; i < 6; ++i)
        {
            if(c == separators[i])
            {
                if(c == ';')
                    printf("%c is Delimiter\n", c);
                else
                    printf("%c is Separator\n", c);
            }
        }


        if(isalnum(c))
            buffer[j++] = c;      

        else if((c == ' ' || c =='\t' || c == '\n') && (j != 0)) 
        {
            buffer[j] = '\0';
            j = 0;
            if(isKeyword(buffer) == 1)
                printf("%s is Keyword\n", buffer);
            else
                printf("%s is Identifier\n", buffer);
        }
    }
    fclose(fp);
    return 0;
}
