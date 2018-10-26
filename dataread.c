#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE* fp;
    char  line[255];
    char id[64];
    char username[64];
    char password[64];
    char my_id[64] = "2";
    fp = fopen("user.txt" , "r");
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // const char * val1 = strtok(line, "|");
        // const char* val2 = strtok(NULL, "|");
        // const char* val3 = strtok(NULL, "|");
        strcpy(id, strtok(line, "|"));;
        strcpy(username, strtok(NULL, "|"));;
        strcpy(password, strtok(NULL, "|"));;
        if(id == my_id){
            printf("IT worked.");
        }
        printf("%s|%s|%s\n", id, username, password);
        
        // printf("%s|%s|%s\n", val1, val2, val3);
    }
}