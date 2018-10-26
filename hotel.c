#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char userInput;
int isLogged = 0;
int isAdmin = 0;

void mainScreen(char a[], char b[], char c[]){
    printf("##############################################\n");
    printf("#              Suite  Bliss                  #\n");
    printf("##############################################\n");
    printf("#                                            #\n");
    printf("               1. %s                          \n", a);
    printf("               2. %s                          \n", b);
    printf("               3. %s                          \n", c);
    printf("#                                            #\n");
    printf("##############################################\n");
}


void msgInfo(char message[]){
    printf("\n##############################################\n");
    printf("%s                        \n", message);
    printf("##############################################\n");
}

void userLogin(){
    // check for login credentials 

}

int main(void){   
    mainScreen("Registration","Login","Exit");
    while(true){
        printf("Please enter an option: ");
        scanf("%d", &userInput);
        switch(userInput){
            case 1: //register();
            case 2: //login();
                msgInfo("Please enter your USER-ID and PASSWORD.");
                break;
            case 3: 
                msgInfo("System has been exited successfully!");
                break;
        }
        break;
    }
    return 0;
}
