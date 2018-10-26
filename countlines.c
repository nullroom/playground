#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countRecords(char *file){
    FILE *fp = fopen(file, "r");
    int ch = 0;
    int lines = 1;
    while(!feof(fp)){
        ch = fgetc(fp);
        if(ch == '\n'){
            lines++;
        }
    }
    return lines;
}

int records;
int main(void) {
        printf("%d",countRecords("user.txt"));
        // records = countRecords("user.txt");
        // printf("%d", records);
        return 0;
    
}