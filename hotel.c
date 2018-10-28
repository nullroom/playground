#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct User {
    int userid;
    int age;
    char id[20];
    char gender[6];
    char name[64];
    char password[64];
};

void read_file(struct User users[]){
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
        fscanf(fp, "%s %s %s", users[j].userid, users[j].name, users[j].password);
        ++j;
    }
    fclose(fp);
}
int isLogged = 0;
void login(char userid[], char password[]){
    char temp_id[64];
    char temp_name[64];
    char temp_password[64];
    FILE *fp;
    fp = fopen("user.txt","r");
        while(fscanf(fp, "%s %s %s", temp_id, temp_name, temp_password) != EOF){
            if(strcmp(temp_id, userid) == 0){
                if(strcmp(temp_password, password) == 0){
                    // printf("Passed");
                    isLogged = 1;
                }
            }
        }
}

struct User users[64];
struct User CurrentUser;
char userInput1;

// count number of records to generate userid
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
    return lines + 1;
}
// register user by adding records to the file
char userReg(int id, char name[], char password[]){
    FILE *fptr;
    fptr = fopen("user.txt","a");
    if(fptr == NULL)
    {
        printf("Error!");   
        exit(1);             
    }
    fprintf(fptr,"%d %s %s\n",id, name, password);
    fclose(fptr);
    printf("----------------------------------------------\n");
    printf("       \nYou have successfully registered!\n\n");
    printf("----------------------------------------------\n");
}
void mainScreen(char a[], char b[], char c[]){
    printf("##############################################\n");
    printf("#              Suite  Bliss                  #\n");
    printf("##############################################\n");
    printf("----------------------------------------------\n");
    printf("               1. %s                          \n", a);
    printf("               2. %s                          \n", b);
    printf("               3. %s                          \n", c);
    printf("----------------------------------------------\n");
    printf("----------------------------------------------\n");
}
void msgInfo(char message[]){
    printf("\n----------------------------------------------\n");
    printf("%s                        \n", message);
    printf("----------------------------------------------\n");
}

int main(void){   
    mainScreen("Registration","Login","Exit");
    while(true){
        printf("Please enter an option: ");
        scanf("%d", &userInput1);
        switch(userInput1){
            case 1: //register();
                msgInfo("Please complete the details below to register.");
                CurrentUser.userid = countRecords("user.txt");
                printf("UserID: %d", CurrentUser.userid);
                printf("\nName: ");
                scanf("%s", &CurrentUser.name);
                printf("Password: ");
                scanf("%s", &CurrentUser.password);
                userReg(CurrentUser.userid, CurrentUser.name, CurrentUser.password);
                continue;
            case 2: //login();
                msgInfo("Please enter your USER-ID and PASSWORD.");
                printf("UserID: ");
                scanf("%s", &CurrentUser.id);
                printf("Password: ");
                scanf("%s", &CurrentUser.password);
                login(CurrentUser.id, CurrentUser.password);
                if(isLogged == 1){
                    printf("Welcome to the booking system.");
                }else{
                    printf("Invalid Credentials.\n\n");
                    continue;
                }
                break;
            case 3: 
                msgInfo("System has been exited successfully!");
                break;
        }
        break;
    }
    return 0;
}
