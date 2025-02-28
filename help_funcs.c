#include "simishell.h"

/**
 * getstr - a function to read a string from  the cli
 * @str: a string pointer 
 * 
 * Return: return 1 in success and -1 in failure
 */

int getstr(char *str)
{
        char **line;
        size_t siz = 0;
        
        line = malloc(24);
        if (!line)
        {
                return (-1);
        }
        
        printprompt(0);
        
        if ((siz =  getline(line, &siz, stdin)) == -1)
        {
                return (-1);
        }

        line[0][siz] = '\0';
  
        strcopy(line[0], str);

        if (line[0][siz - 2] == '\\')
        {       do 
                {
                        str[strleng(str) - 1] = ' ';
                        siz = 0;
                        printprompt(1);

                        if ((siz =  getline(line, &siz, stdin)) == -1)
                        {
                                                return (-1);
                        }
                        line[0][siz] = '\0';

                        strmix(line[0], str);
                }  while (line[0][siz - 2] == '\\');
        }

        free(line);
        return (1);
}

/**
 * strcopy - a function to copy to strings
 * @src: the string to be copied
 * @dest: the destination of the copied string
 * 
 * Return: returns nothing (void)
 */

void strcopy(char *src, char *dest)
{
    int i = 0;
    int j = 0;

    if (!dest)
    {
            j = 0;
    }
    
    while(src[i] != '\0' && src[i] != '\n')
    {
        dest[j++] = src[i++];
    }
    
    dest[j] = '\0';
}

/**
 * strmix - a function to copy to strings and concatenate if
 *           the destination have a string already.
 * @src: the string to be copied
 * @dest: the destination of the copied string
 * 
 * Return: returns nothing (void)
 */

void strmix(char *src, char *dest)
{
    int i = 0;
    int j;
    
    if (!dest)
    {
        j = 0;
    }
    else
    {
        j = strleng(dest);
    }
    
    while(src[i] != '\0' && src[i] != '\n')
    {
        dest[j++] = src[i++];
    }
    
    dest[j] = '\0';
}

/**
 * strbrk: a function that breaks a long string in to arrauy of strings
 * @line: the string to be breakdown
 * 
 * Return: returns the array of the words.
 */

char **strbrk(char *line)
{
        int i = 0, j = 0, k;
        char **array;
        
        if (!line || line[0] == '\0')
        {
            return (NULL);
        }
        
        array = malloc(sizeof(*array) * 128);
        if (array == NULL)
        {
                perror("Couldn't Allocate");
                return (NULL);
        }

        while(line[i] != '\0')
        {
                if (j > 120)
                {
                    array = realloc(array, sizeof(*array) * (i + 16));
                    if (array == NULL)
                    {
                        perror("Couldn't Reallocate");
                        return (NULL);
                    }
                }
                    
                if (line[i] == ' ')
                {
                        i++;
                        continue;
                }

                array[j] = malloc(sizeof(**array) * 64);
                if (array[j] == NULL)
                {
                    perror("Couldn't Allocate");
                    return (NULL);
                }
                
                k = 0;
                while(line[i] != ' ' && line[i] != '\0')
                {
                        array[j][k] = line[i++];
                        k++;
                        
                        if (k > 60)
                        {
                            array[j] = realloc(array[j], sizeof(*array) * (k + 8));
                            if (array[j] == NULL)
                            {
                                perror("Couldn't Reallocate");
                                return (NULL);
                            }
                        }
                }
                array[j][k] = '\0'; 
                j++;
        }

        array[j] = NULL;
        
        return array;
}

/**
 * strleng - measures a length of a string
 * @s: a string location pointer
 * Return: returns length
 */ 
 
int strleng(char *s)
{
  int len = 0;

  while (s[len] != '\0')
    {
      len++;
    }

  return len;
}
