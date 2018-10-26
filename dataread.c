#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE* fp;
    char  line[255];


    fp = fopen("user.txt" , "r");
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        const char* val1 = strtok(line, "|");
        const char* val2 = strtok(NULL, "|");
        const char* val3 = strtok(NULL, "|");

        printf("%s|%s|%s\n", val1, val2, val3);
    }
}