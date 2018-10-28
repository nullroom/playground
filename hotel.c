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

// Booking System START
void bookMenu(char a[], char b[], char c[], char d[]){
    printf("##############################################\n");
    printf("#         Welcome to Suite Bliss!            #\n");
    printf("##############################################\n");
    printf("# User-ID: %s                                 \n", d);
    printf("----------------------------------------------\n");
    printf("               1. %s                          \n", a);
    printf("               2. %s                          \n", b);
    printf("               3. %s                          \n", c);
    printf("----------------------------------------------\n");
    printf("----------------------------------------------\n");
}

struct Booking {
    int roomId; // identifier for room type
    int roomNumber; 
    int roomCapacity;
    int userCapacity;
    int checkinYear;
    int checkinMonth;
    int checkinDay;
    int checkoutMonth;
    int checkoutDay;
    char roomType[64];
    int idRegistered;
    int availableRooms;
};
struct Booking Availability; 
struct Booking Available[100]; // gathered list of available rooms


void availability(int roomID, int userCapacity, int cY, int cM, int cD, int cm, int cd){
    int tmpID;
    int tmproomNum;
    int tmproomCap;
    int tmpuserCap;
    int tmpcY;
    int tmpcM;
    int tmpcD;
    int tmpcm;
    int tmpcd;
    char tmptype[64];
    int tmpuserID;
    int i = 0;
    FILE *fp;
    fp = fopen("rooms.txt","r");
        while(fscanf(fp, "%d %d %d %d %d %d %d %d %s %d", &tmpID, &tmproomNum, &tmproomCap, &tmpcY, &tmpcM, &tmpcD, &tmpcm, &tmpcd, tmptype, &tmpuserID) != EOF){
            if(tmpID == roomID){ // validate/get room type
                if(userCapacity <= tmproomCap){ // validate capacity
                    if((tmpcY == cY) && (((tmpcM == cM) && (tmpcD <= cD )) || (tmpcM > cM))){ // validate check in date
                        if((tmpcm > cm) || ((tmpcm == cm) && (tmpcd > cd ))){ // validate check out date
                            if(tmpuserID == 0){ // validate room vacancy - 0 means empty
                                Available[i].roomId = tmpID;
                                Available[i].roomNumber = tmproomNum;
                                Available[i].roomCapacity = tmproomCap;
                                Available[i].userCapacity = userCapacity;
                                Available[i].checkinYear = cY;
                                Available[i].checkinMonth = cM;
                                Available[i].checkinDay = cD;
                                Available[i].checkoutMonth = cm;
                                Available[i].checkoutDay = cd;
                                strcpy(Available[i].roomType, tmptype);
                                i++;
                            }
                        }
                    }
                }
            }
        }
        Available[0].availableRooms = i;
        fclose(fp);
}
// Booking System END

struct User users[64];
struct User CurrentUser;
char userInput1;
char userInput2;
char userInput3;

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
        system("cls");
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
                    system("cls");
                    while(true){
                        bookMenu("Bookings", "Modify Booking", "View Status", CurrentUser.id);
                        printf("Please enter an option: ");
                        scanf("%d", &userInput2);
                        system("cls");
                        switch(userInput2){
                            case 1:
                                bookMenu("Availability Check", "Reservation", "Go Back", CurrentUser.id);
                                printf("Please enter an option: ");
                                scanf("%d", &userInput3);
                                system("cls");
                                switch(userInput3){
                                    case 1:
                                        bookMenu("Duplex", "Single Bedroom", "Double Bedroom", CurrentUser.id);
                                        printf("Select Room Type: ");
                                        scanf("%d", &Availability.roomId);
                                        // printf("No. of adults/kids: ");
                                        // scanf("%d", &Availability.userCapacity);
                                        // printf("Check In Date: \n");
                                        // printf("Year: ");
                                        // scanf("%d", &Availability.checkinYear);
                                        // printf("Month (in number): ");
                                        // scanf("%d", &Availability.checkinMonth);
                                        // printf("Day: ");
                                        // scanf("%d", &Availability.checkinDay);
                                        // printf("----------------------------------------------\n");
                                        // printf("Check Out Date: \n");
                                        // printf("Month: ");
                                        // scanf("%d", &Availability.checkoutMonth);
                                        // printf("Day: ");
                                        // scanf("%d", &Availability.checkoutDay);
                                        // availability(Availability.roomId, Availability.userCapacity, Availability.checkinYear, Availability.checkinMonth, Availability.checkinDay, Availability.checkoutMonth, Availability.checkoutDay);
                                        availability(1,4,2018,11,26,11,30);
                                        printf("----------------------------------------------\n");
                                        printf("Available Rooms: %d                           \n", Available[0].availableRooms);
                                        for(int j = 0; j < Available[0].availableRooms; j++){
                                            printf("----------------------------------------------\n");
                                            printf("Room Number: %d\n", Available[j].roomNumber);
                                            printf("Room Type: %s\n", Available[j].roomType);
                                            printf("Capacity: %d\n", Available[j].roomCapacity);
                                            printf("----------------------------------------------\n");

                                        }
                                        printf("Would you like to continue? (y/n):");
                                        char cont;
                                        scanf("%s", &cont);
                                        if(cont == 'y'){
                                            continue;
                                        }
                                        // for(int j = 0; j <= i; j++){
                                        //     printf("%d", Available[j].roomNumber);
                                        // }
                                    case 2:
                                    case 3:
                                        break;
                                }
                        }

                    }
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
