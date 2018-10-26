#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int userLogin(char userid, char password[]){
    int state = 0;
    FILE* fp;
    char  line[255];

    fp = fopen("user.txt" , "r");
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        const char* val1 = strtok(line, "|");
        const char* val2 = strtok(NULL, "|");
        const char* val3 = strtok(NULL, "|");
        int test = (uintptr_t)var1;
        if(userid == test){
            printf("User passed");
            state = 1;
        }
        // printf("%s|%s|%s\n", val1, val2, val3);
        printf("%s", test);
    }
    // return state;
}

int main(void){
    printf("%s", userLogin(3, "Test"));
    return 0;
}