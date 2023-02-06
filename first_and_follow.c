#include<stdio.h>
#include<ctype.h>
#include<string.h>

char prods[50][50];
char first[26][50];
int first_done[26];
char follow[26][50];
int follow_done[26];
int n;

void First(char nonterm)  // Computing FIRST for the given non terminal
{
    char curr_first[26];
    int index = 0;
    
    for(int i=0;i<n;i++)
    {
        if(prods[i][0]== nonterm)  
        {
            if(!isupper(prods[i][2])) // If its a terminal symbol then add it to first
            {
                curr_first[index] = prods[i][2];
                index++;
                continue;
            }

            int flag = 0;
            int prod_idx = 2;

            while(prods[i][prod_idx]!='\0' && flag == 0)
            {
                flag = 1;

                if(first_done[prods[i][prod_idx]-65] == 0) // If its a non terminal then its first is added 
                    First(prods[i][prod_idx]);             //Compute its first is not yet computed
                
                int idx = 0;
                while(first[prods[i][prod_idx]-65][idx] != '\0')
                {
                    curr_first[index] = first[prods[i][prod_idx]-65][idx];
                    if(first[prods[i][prod_idx]-65][idx] == 'e') //If it includes epsilon then the next symbol is to be considered
                    {
                        flag = 0;
                        prod_idx++;
                    }
                    index++;
                    idx++;
                }                
            }           
        }
    }

    curr_first[index] = '\0';
    strcpy(first[nonterm-65],curr_first);
    first_done[nonterm-65] = 1;
    
}

void Follow(char nonterm)
{
    char curr_follow[50];
    int index = 0;

    if(prods[0][0] == nonterm)
    {
        curr_follow[index] = '$';
        index++;
    }

    for(int i=0;i<n;i++)
    {
        int flag = 0;
        for(int prod_idx=2;prods[i][prod_idx] != '\0';prod_idx++)
        {
            if(prods[i][prod_idx] == nonterm || flag == 1 )
            {
                flag = 0;
                if(prods[i][prod_idx+1] != '\0')
                {
                    if(!isupper(prods[i][prod_idx + 1]))
                    {
                        curr_follow[index] = prods[i][prod_idx + 1];
                        index++;
                        continue;
                    }

                    int idx = 0;
                    while(first[prods[i][prod_idx+1]-65][idx] != '\0')
                    {
                        if(first[prods[i][prod_idx+1]-65][idx] == 'e')
                        {
                            flag = 1;
                            idx++;
                            continue;
                        }

                        int temp_flag = 1;
                        for(int j=0;j<index;j++)
                        {
                            if(first[prods[i][prod_idx+1]-65][idx] == curr_follow[j])
                            {
                                temp_flag = 0;
                                break;
                            }
                        }

                        if(temp_flag == 1)
                        {
                            curr_follow[index] = first[prods[i][prod_idx+1]-65][idx];
                            index++;
                        }
                        idx++;
                    }
                }
                else
                {
                    if(prods[i][0] != nonterm)
                    {
                        if(follow_done[prods[i][0]-65] == 0)
                            Follow(prods[i][0]);

                        int idx = 0;
                        while(follow[prods[i][0]-65][idx] != '\0')
                        {
                            int temp_flag = 1;
                            for(int j=0;j<index;j++)
                            {
                                if(follow[prods[i][0]-65][idx] == curr_follow[j])
                                {
                                    temp_flag = 0;
                                    break;
                                }
                            }

                            if(temp_flag == 1)
                            {
                                curr_follow[index] = follow[prods[i][0]-65][idx];
                                index++;
                            }
                            idx++;
                        }                         
                    }
                }
            }
        }
    }
    curr_follow[index] = '\0';
    strcpy(follow[nonterm-65],curr_follow);
    follow_done[nonterm-65] = 1;
}

void main()
{
    char ch;
    printf("\nEnter the no. of productions: ");
    scanf("%d",&n);
    printf("\nEnter the productions:\n");
    for(int i=0;i<n;i++)
        scanf("%s",prods[i]);    
    for(int i=0;i<26;i++)
    {
        first_done[i] = 0;
        follow_done[i] = 0;
    }

    for(int i=0;i<n;i++)
    {
        if(first_done[prods[i][0]-65] == 0)
            First(prods[i][0]);
    }

    printf("\n____FIRST____\n\n");
    for(int i=0;i<26;i++)
    {
        if (first_done[i] == 1)
        {
            printf("%c : { ",i+65);
            for(int j=0;j<strlen(first[i]);j++)
            {
                printf("%c",first[i][j]);
                if(j != strlen(first[i])-1)
                    printf(", ");
            }
            printf(" }\n");
        }
    }

    for(int i=0;i<n;i++)
    {
        if(follow_done[prods[i][0]-65] == 0)
            Follow(prods[i][0]);
    }

    printf("\n____FOLLOW____\n\n");
    for(int i=0;i<26;i++)
    {
        if (follow_done[i] == 1)
        {
            printf("%c : { ",i+65);
            for(int j=0;j<strlen(follow[i]);j++)
            {
                printf("%c",follow[i][j]);
                if(j != strlen(follow[i])-1)
                    printf(", ");
            }
            printf(" }\n");
        }
    }
}