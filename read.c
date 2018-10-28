#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct account {
    char id[20];
    char name[20];
    char password[20];
};

struct account accounts[10];
// void read_file(struct account accounts[]){
//     FILE *fp;
//     int i = 0;
//     int c;
//     fp = fopen("user.txt","r");
//     while(!feof(fp)){
//         c = fgetc(fp);
//         if(c == '\n'){
//             ++i;
//         }
//     }
//         int j = 0;
//         rewind(fp);

//         while(j != i - 1){
//             fscanf(fp, "%s %s %s", accounts[j].id, accounts[j].name, accounts[j].password);
//             ++j;
//         }
//     }

void read_file(struct account accounts[]){
    FILE *fp;
    int i = 0;
    int c;
    fp = fopen("user.txt","r");
    while(!feof(fp)){
        c = fgetc(fp);
        if(c == '\n'){
            ++i;
        }
    }
        int j = 0;
        rewind(fp);

        while(j != i - 1){
            fscanf(fp, "%s %s %s", accounts[j].id, accounts[j].name, accounts[j].password);
            ++j;
        }
    }



int main(void) {
    int iii = 2;
    char * ii;
    sprintf(ii, "%d", iii);
    const char * user = "Billy"; 
    read_file(accounts);
    if(strcmp(ii, accounts[0].id) == 0){
        printf("Success1");
        if(strcmp(user, accounts[0].name) == 0){
            printf("Success2");
        }
    }
    // printf("%s", ii);
    // printf("%s", accounts[0].id);
    // char username[64];
    // char password[64];
    // FILE *ptr_file;
    // char buf[1000];

    // ptr_file = fopen("user.txt", "r");
    // if(!ptr_file)
    //     return 1;
    // while(fgets(buf, 1000, ptr_file)!= NULL){
    //     printf(fscanf(ptr_file,"%s %s %s %s", &username, &password));
    // }
        

    //     fclose(ptr_file);
    //     return 0;
    
}