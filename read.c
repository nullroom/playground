#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char username[64];
    char password[64];
    FILE *ptr_file;
    char buf[1000];

    ptr_file = fopen("user.txt", "r");
    if(!ptr_file)
        return 1;
    while(fgets(buf, 1000, ptr_file)!= NULL){
        printf(fscanf(ptr_file,"%s %s %s %s", &username, &password));
    }
        

        fclose(ptr_file);
        return 0;
    
}