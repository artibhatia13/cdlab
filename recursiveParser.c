/*
    Diya Naushad CS6A Rollno.23
    
    Productions:
    S -> var = B;
    A -> var * A | var 
    B -> A * C * A | C * A | A * C
    C -> ( var + var)

    Syntax: var =  ( var + var ) * var ;  with multiple multiplication and term within parenthesis can appear only once.
*/

#include <stdio.h>
#include <string.h>
#include<ctype.h>
char *t,*temp, delimiter[] = " ",str[50];
int flag;

int var(char* s)
{
   int len = strlen(s);
   if(len==1 && isalpha(s[0]))
        return 1;
   if(!isalpha(s[0]))
        return 0;
   for(int i=1;i<len;i++)
   if (!isalpha(s[i]) && !isdigit(s[i]))
        return 0;
   return 1;
}

void C()
{
    if(*t == '(')
    {
        t = strtok(NULL, delimiter);
        if(var(t)==1)
        {
            t = strtok(NULL, delimiter);
            if(*t == '+')
            {
                t = strtok(NULL, delimiter);
                if(var(t)==1)
                {
                    t = strtok(NULL, delimiter);
                    if(*t == ')')
                    {
                        t = strtok(NULL, delimiter);
                        flag = 1;
                    }
                    else
                        flag = 0;
                }
                else
                    flag = 0;
            }
            else
                flag = 0;
        }
        else    
            flag = 0;
    }
    else
        flag = 0;
    
}

void A()           
{ 
    temp = t;
    if(var(t)==1)
    {
        t = strtok(NULL, delimiter);
        if(*t == '*')
        {
           t = strtok(NULL, delimiter);
           A();
        } 
        flag = 1;     
    } 
    else
        flag = 0;   
}

void B()                               
{
    temp = t;
    
    A();
    if( flag == 1)
    {
        C();
        if( *t == '*')
        {
            t = strtok(NULL, delimiter);
            A();
        }

        else if (flag == 1)
        {
            flag = 1;
        }    
    }
    

    if(flag == 0)
    {
        t = temp;
        C();
        if(*t=='*')
        {
            t = strtok(NULL, delimiter);
            A();    
                    
        }
        else
            flag = 0;
    }
}

void S()                 
{
    if(var(t)== 1)
    {
        t = strtok(NULL, delimiter);
        if(*t == '=')
        {
            t = strtok(NULL, delimiter);
            B();            
            if(flag == 1 && *t ==';')
            {
                t = strtok(NULL, delimiter);
                flag = 1;
            }    
            else
                flag = 0;
        }
        else
            flag = 0;
    }
    else
        flag = 0;
}


int main()
{
  printf("\nSyntax: var = (var + var) * var ; with multiple multiplication and term within parenthesis can appear only once.\n");
  printf("\nEnter the Statement (use " " as the delimiter) : ");
  fgets(str,50,stdin);  
  t = strtok(str, delimiter);
  flag=1;
  S();
  if(t == NULL && flag==1)
    printf("Syntax verified\n");
  else
  printf("Syntax error\n");
  
  printf("\n");
  return 0;
}