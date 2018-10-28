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
struct User users[64];
struct User CurrentUser;
char userInput1;
char userInput2;
char userInput3;
char userInput4;
int isLogged = 0;

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
    char reason[64];
};
struct Booking Availability; 
struct Booking Available[100]; // gathered list of available rooms
struct Booking Booked; // create reservation
struct Booking Modify; // modify reservation
struct Booking Cancel; // cancel reservation

void availability(int roomID, int userCapacity, int cY, int cM, int cD, int cm, int cd){
    int tmpID, tmproomNum, tmproomCap, tmpuserCap, tmpcY, tmpcM, tmpcD, tmpcm, tmpcd, tmpuserID;;
    char tmptype[64];
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

void bookRoom(int roomNum, char name[], int age, char gender[], int cY, int cM, int cD, int cm, int cd, char userID[]){
    int tmpID, tmproomNum, tmproomCap, tmpuserCap, tmpcY, tmpcM, tmpcD, tmpcm, tmpcd, tmpuserID;
    char tmptype[64];
    int i = 0;
    FILE *fp, *fpout, *fpout2;
    fp = fopen("rooms.txt","r");
    fpout = fopen("tmp_rooms.txt", "w");
    fpout2 = fopen("booked.txt", "a");
        while(fscanf(fp, "%d %d %d %d %d %d %d %d %s %d", &tmpID, &tmproomNum, &tmproomCap, &tmpcY, &tmpcM, &tmpcD, &tmpcm, &tmpcd, tmptype, &tmpuserID) != EOF){
            if(tmproomNum == roomNum){
                fprintf(fpout, "%d %d %d %d %d %d %d %d %s %s\n", tmpID, tmproomNum, tmproomCap, tmpcY, tmpcM, tmpcD, tmpcm, tmpcd, tmptype, userID);
                fprintf(fpout2, "%d %s %d %s %d %d %d %d %d %s\n", roomNum, name, age, gender, cY, cM, cD, cm, cd, userID);
            }else{
                fprintf(fpout, "%d %d %d %d %d %d %d %d %s %d\n", tmpID, tmproomNum, tmproomCap, tmpcY, tmpcM, tmpcD, tmpcm, tmpcd, tmptype, tmpuserID);
            }
        }
        fclose(fp);
        fclose(fpout);
        fclose(fpout2);
        remove("rooms.txt");
        rename("tmp_rooms.txt", "rooms.txt");
}

void modifyRoom(int roomNum, int cY, int cM, int cD, int cm, int cd, char userID[]){
    int tmproomNum, tmpAge, tmpcY, tmpcM, tmpcD, tmpcm, tmpcd, tmpuserID;
    char name[64];
    char gender[64];
    int i = 0;
    FILE *fp, *fpout;
    fp = fopen("booked.txt","r");
    fpout = fopen("tmp_booked.txt", "w");
        while(fscanf(fp, "%d %s %d %s %d %d %d %d %d %d", &tmproomNum, &name, &tmpAge, &gender, &tmpcY, &tmpcM, &tmpcD, &tmpcm, &tmpcd, &tmpuserID) != EOF){
            if(tmproomNum == roomNum){
                fprintf(fpout, "%d %s %d %s %d %d %d %d %d %s\n", roomNum, name, tmpAge, gender, cY, cM, cD, cm, cd, userID);
            }else{
                fprintf(fpout, "%d %s %d %s %d %d %d %d %d %s\n", tmproomNum, name, tmpAge, gender, tmpcY, tmpcM, tmpcD, tmpcm, tmpcd, userID);
            }
        }
        fclose(fp);
        fclose(fpout);
        remove("booked.txt");
        rename("tmp_booked.txt", "booked.txt");
}

void cancelRoom(int roomNum, char reason[]){
    int tmproomNum, tmpAge, tmpcY, tmpcM, tmpcD, tmpcm, tmpcd, tmpuserID;
    char name[64];
    char gender[64];
    FILE *fp, *fpout, *fpout1;
    fp = fopen("booked.txt","r");
    fpout = fopen("cancellation.txt", "w");
    // fpout1 = fopen("tmp_booked.txt", "w");
        while(fscanf(fp, "%d %s %d %s %d %d %d %d %d %d", &tmproomNum, &name, &tmpAge, &gender, &tmpcY, &tmpcM, &tmpcD, &tmpcm, &tmpcd, &tmpuserID) != EOF){
            if(tmproomNum == roomNum){
                fprintf(fpout, "%d %s %d %s %d %d %d %d %d %s\n", roomNum, name, tmpAge, gender, tmpcY, tmpcM, tmpcD, tmpcm, tmpcd, reason);
            }else{
                fprintf(fpout1, "%d %s %d %s %d %d %d %d %d %s\n", roomNum, name, tmpAge, gender, tmpcY, tmpcM, tmpcD, tmpcm, tmpcd, tmpuserID);
            }
        }
        fclose(fp);
        // fclose(fpout1);
        fclose(fpout);
        // remove("booked.txt");
        // rename("tmp_booked.txt", "booked.txt");
}

// Booking System END

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
                    while(true){
                        system("cls");
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
                                        printf("No. of adults/kids: ");
                                        scanf("%d", &Availability.userCapacity);
                                        printf("Check In Date: \n");
                                        printf("Year: ");
                                        scanf("%d", &Availability.checkinYear);
                                        printf("Month (in number): ");
                                        scanf("%d", &Availability.checkinMonth);
                                        printf("Day: ");
                                        scanf("%d", &Availability.checkinDay);
                                        printf("----------------------------------------------\n");
                                        printf("Check Out Date: \n");
                                        printf("Month: ");
                                        scanf("%d", &Availability.checkoutMonth);
                                        printf("Day: ");
                                        scanf("%d", &Availability.checkoutDay);
                                        availability(Availability.roomId, Availability.userCapacity, Availability.checkinYear, Availability.checkinMonth, Availability.checkinDay, Availability.checkoutMonth, Availability.checkoutDay);
                                        // availability(1,4,2018,11,26,11,30);
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
                                    case 2:
                                        system("cls");
                                        msgInfo("Enter details to make Reservation");
                                        printf("Room Number: ");
                                        scanf("%d", &Booked.roomNumber);
                                        printf("Name: ");
                                        scanf("%s", &CurrentUser.name);
                                        printf("Age: ");
                                        scanf("%d", &CurrentUser.age);
                                        printf("Gender: ");
                                        scanf("%s", &CurrentUser.gender);
                                        printf("Check-In Date: \n");
                                        printf("Year: ");
                                        scanf("%d", &Booked.checkinYear);
                                        printf("Month: ");
                                        scanf("%d", &Booked.checkinMonth);
                                        printf("Day: ");
                                        scanf("%d", &Booked.checkinDay);
                                        printf("Check-Out Date: \n");
                                        printf("Month: ");
                                        scanf("%d", &Booked.checkoutMonth);
                                        printf("Day: ");
                                        scanf("%d", &Booked.checkoutDay);
                                        bookRoom(Booked.roomNumber, CurrentUser.name, CurrentUser.age, CurrentUser.gender, Booked.checkinYear, Booked.checkinMonth, Booked.checkinDay, Booked.checkoutMonth, Booked.checkoutDay, CurrentUser.id);
                                        system("cls");
                                        msgInfo("Room Booking Confirmation");
                                        printf("----------------------------------------------\n");
                                        printf("Room Number: %d\n", Booked.roomNumber);
                                        printf("Name: %s\n", CurrentUser.name);
                                        printf("Age: %d\n", CurrentUser.age);
                                        printf("Gender: %s\n", CurrentUser.gender);
                                        printf("CheckIn Date: %d/%d/%d\n", Booked.checkinDay, Booked.checkinMonth, Booked.checkinYear);
                                        printf("CheckOut Date: %d/%d/%d\n", Booked.checkoutDay, Booked.checkinMonth);
                                        printf("----------------------------------------------\n");
                                        printf("Would you like to continue? (y/n):");
                                        char cont1;
                                        scanf("%s", &cont1);
                                        if(cont1 == 'y'){
                                            continue;
                                        }
                                    case 3:
                                        break;
                                }
                            case 2:
                                bookMenu("Modify Reservation", "Cancellation", "Go Back", CurrentUser.id);
                                printf("Please enter an option: ");
                                scanf("%d", &userInput4);
                                switch(userInput4){
                                    case 1:
                                        msgInfo("Modify Room Reservation");
                                        printf("Enter room number: ");
                                        scanf("%d", &Modify.roomNumber);
                                        printf("New Check In Date: \n");
                                        printf("----------------------------------------------\n");
                                        printf("Year: ");
                                        scanf("%d", &Modify.checkinYear);
                                        printf("Month: ");
                                        scanf("%d", &Modify.checkinMonth);
                                        printf("Day: ");
                                        scanf("%d", &Modify.checkinDay);
                                        printf("----------------------------------------------\n");
                                        printf("New Check Out Date: \n");
                                        printf("----------------------------------------------\n");
                                        printf("Month: ");
                                        scanf("%d", &Modify.checkoutMonth);
                                        printf("Day: ");
                                        scanf("%d", &Modify.checkoutDay);
                                        modifyRoom(Modify.roomNumber, Modify.checkinYear, Modify.checkinMonth, Modify.checkinDay, Modify.checkoutMonth, Modify.checkoutDay, CurrentUser.id);
                                        msgInfo("Booking Successfully Modified");
                                        char cont2;
                                        printf("Would you like to continue? (y/n): ");
                                        scanf("%s", &cont2);
                                        if(cont2 == 'y'){
                                            break;
                                        }
                                    case 2:
                                        msgInfo("Room Reservation Cancellation");
                                        printf("Enter room number: ");
                                        scanf("%d", &Cancel.roomNumber);
                                        printf("Reason: ");
                                        scanf("%s", &Cancel.reason);
                                        cancelRoom(Cancel.roomNumber, Cancel.reason);
                                        msgInfo("Reservation Successfully Cancelled");
                                        printf("Would you like to continue? (y/n):");
                                        char cont3;
                                        if(cont3 == 'y'){
                                            break;
                                        }
                                }
                        }
                    // break;
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
