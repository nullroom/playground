#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct User {
    int userid;
    int age;
    char gender[6];
    char name[64];
    char password[64];
};

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
    fprintf(fptr,"%d|%s|%s\n",id, name, password);
    fclose(fptr);
    printf("----------------------------------------------\n");
    printf("       \nYou have successfully registered!\n\n");
    printf("----------------------------------------------\n");
}

int userLogin(char username[], char password[]){
    
}

struct User CurrentUser;

int userLogged = 0;
char userInput;
int isLogged = 0;
int isAdmin = 0;

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
        scanf("%d", &userInput);
        switch(userInput){
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
                scanf("%d", &CurrentUser.userid);
                printf("Password: ");
                scanf("%s", &CurrentUser.password);
                break;
            case 3: 
                msgInfo("System has been exited successfully!");
                break;
        }
        break;
    }
    return 0;
}
