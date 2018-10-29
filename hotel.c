#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct User {
    int userid;
    int age;
    char id[20];
    char gender[64];
    char name[64];
    char password[64];
};
struct User users[100];
struct User CurrentUser;
char userInput1;
char userInput2;
char userInput3;
char userInput4;
char userInput5;
int isLogged = 0;
// admin panel START
int isAdmin = 0;
int aOption1; // first admin option
int aOption1a; // first admin sub option
int aOption2; 

// admin panel STOP

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

int login(char userid[], char password[]){
    char temp_id[64];
    char temp_name[64];
    char temp_password[64];
    FILE *fp;
    fp = fopen("user.txt","r");
    while(fscanf(fp, "%s %s %s", temp_id, temp_name, temp_password) != EOF){
            if(strcmp(temp_id, userid) == 0){
                if(strcmp(temp_password, password) == 0){
                    return 1;
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
    int reservations;

};
struct Booking Availability; 
struct Booking Available[100]; // gathered list of available rooms
struct Booking Booked; // create reservation
struct Booking Modify; // modify reservation
struct Booking Cancel; // cancel reservation
struct Booking Reservation[100]; // store reservation details

// admin section START
struct Booking roomView[100]; // view rooms 
struct Booking resView[100]; // view reservations 
struct Booking searchRes[100]; // search reservations 
struct Booking cancellations[100]; // list of cancelled bookings 
// admin section STOP

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
    FILE *fp, *fpout, *fpout4;
    fp = fopen("booked.txt","a+");
    fpout = fopen("cancellation.txt", "w");
    fpout4 = fopen("tmps_booked.txt", "w");
        while(fscanf(fp, "%d %s %d %s %d %d %d %d %d %d", &tmproomNum, &name, &tmpAge, &gender, &tmpcY, &tmpcM, &tmpcD, &tmpcm, &tmpcd, &tmpuserID) != EOF){
            if(tmproomNum == roomNum){
                fprintf(fpout, "%d %s %d %s %d %d %d %d %d %d %s\n", tmproomNum, name, tmpAge, gender, tmpcY, tmpcM, tmpcD, tmpcm, tmpcd, tmpuserID, reason);
                
            }else{
                fprintf(fpout4, "%d %s %d %s %d %d %d %d %d %d\n", tmproomNum, name, tmpAge, gender, tmpcY, tmpcM, tmpcD, tmpcm, tmpcd, tmpuserID);
            }
        }
        fclose(fpout4);
        fclose(fp);
        fclose(fpout);
        remove("booked.txt");
        rename("tmps_booked.txt", "booked.txt");
}

void reservations(int userid){ // user reservations
    int tmproomNum, tmpAge, tmpcY, tmpcM, tmpcD, tmpcm, tmpcd;
    int tmpuserID;
    char name;
    char gender[64];
    int i = 0;
    FILE *fp;
    fp = fopen("booked.txt","r");
        while(fscanf(fp, "%d %s %d %s %d %d %d %d %d %d", &tmproomNum, &name, &tmpAge, &gender, &tmpcY, &tmpcM, &tmpcD, &tmpcm, &tmpcd, &tmpuserID) != EOF){
            if(tmpuserID == userid){
                Reservation[i].roomNumber = tmproomNum;
                Reservation[i].checkinYear = tmpcY;
                Reservation[i].checkinMonth = tmpcM;
                Reservation[i].checkinDay = tmpcD;
                Reservation[i].checkoutMonth = tmpcm;
                Reservation[i].checkoutDay = tmpcd;
                i++;
            }
        }
        Reservation[0].reservations = i;
        fclose(fp);
}

// Booking System END

void viewRoom(){
    int tmpID, tmproomNum, tmproomCap, tmpuserCap, tmpcY, tmpcM, tmpcD, tmpcm, tmpcd, tmpuserID;;
    char tmptype[64];
    int i = 0;
    FILE *fp;
    fp = fopen("rooms.txt","r");
        while(fscanf(fp, "%d %d %d %d %d %d %d %d %s %d", &tmpID, &tmproomNum, &tmproomCap, &tmpcY, &tmpcM, &tmpcD, &tmpcm, &tmpcd, tmptype, &tmpuserID) != EOF){
            roomView[i].roomId = tmpID;
            roomView[i].roomNumber = tmproomNum;
            roomView[i].roomCapacity = tmproomCap;
            roomView[i].checkinYear = tmpcY;
            roomView[i].checkinMonth = tmpcM;
            roomView[i].checkinDay = tmpcD;
            roomView[i].checkoutMonth = tmpcm;
            roomView[i].checkoutDay = tmpcd;
            strcpy(roomView[i].roomType, tmptype);
            i++;                         
        }
        roomView[0].availableRooms = i;
        fclose(fp);
}

void searchReservations(int roomNum){
    int tmproomNum, tmpAge, tmpcY, tmpcM, tmpcD, tmpcm, tmpcd, tmpuserID;;
    char tmpGender[64];
    char tmpName[64];
    FILE *fp;
    fp = fopen("booked.txt","r");
        while(fscanf(fp, "%d %s %d %s %d %d %d %d %d %d", &tmproomNum, &tmpName, &tmpAge, &tmpGender, &tmpcY, &tmpcM, &tmpcD, &tmpcm, &tmpcd, &tmpuserID) != EOF){
            if(tmproomNum == roomNum){
                searchRes[0].roomNumber = tmproomNum;
                strcpy(users[0].name, tmpName);
                users[0].age = tmpAge;
                strcpy(users[0].gender, tmpGender);
                searchRes[0].checkinYear = tmpcY;
                searchRes[0].checkinMonth = tmpcM;
                searchRes[0].checkinDay = tmpcD;
                searchRes[0].checkoutMonth = tmpcm;
                searchRes[0].checkoutDay = tmpcd;
            }
        }
        fclose(fp);
}

void viewReservations(){
    int tmproomNum, tmpAge, tmpcY, tmpcM, tmpcD, tmpcm, tmpcd, tmpuserID;;
    char tmpName[64];
    char tmpGender[64];
    int i = 0;
    FILE *fp;
    fp = fopen("booked.txt","r");
        while(fscanf(fp, "%d %s %d %s %d %d %d %d %d %d", &tmproomNum, tmpName, &tmpAge, tmpGender, &tmpcY, &tmpcM, &tmpcD, &tmpcm, &tmpcd, &tmpuserID) != EOF){
            resView[i].roomNumber = tmproomNum;
            strcpy(users[i].name, tmpName);
            strcpy(users[i].gender, tmpGender);
            users[i].age = tmpAge;
            resView[i].checkinYear = tmpcY;
            resView[i].checkinMonth = tmpcM;
            resView[i].checkinDay = tmpcD;
            resView[i].checkoutMonth = tmpcm;
            resView[i].checkoutDay = tmpcd;
            i++;                         
        }
        resView[0].availableRooms = i;
        fclose(fp);
}

void viewCancellations(){
    int tmproomNum, tmpAge, tmpcY, tmpcM, tmpcD, tmpcm, tmpcd, tmpuserID;;
    char tmpName[64];
    char tmpGender[64];
    char tmpReason[64];
    int i = 0;
    FILE *fp;
    fp = fopen("cancellation.txt","r");
        while(fscanf(fp, "%d %s %d %s %d %d %d %d %d %d %s", &tmproomNum, tmpName, &tmpAge, tmpGender, &tmpcY, &tmpcM, &tmpcD, &tmpcm, &tmpcd, &tmpuserID, tmpReason) != EOF){
            cancellations[i].roomNumber = tmproomNum;
            strcpy(users[i].name, tmpName);
            strcpy(users[i].gender, tmpGender);
            strcpy(cancellations[i].reason, tmpReason);
            users[i].age = tmpAge;
            cancellations[i].checkinYear = tmpcY;
            cancellations[i].checkinMonth = tmpcM;
            cancellations[i].checkinDay = tmpcD;
            cancellations[i].checkoutMonth = tmpcm;
            cancellations[i].checkoutDay = tmpcd;
            i++;                         
        }
        cancellations[0].availableRooms = i;
        fclose(fp);
}

void editRoom(int roomNum, int roomCapacity, int startY, int startM, int startD, int endM, int endD){ // edit room properties by admin
    int tmproomID, tmproomNum, tmpCap, tmpcY, tmpcM, tmpcD, tmpcm, tmpcd, tmpuserID;
    char tmptype[64];
    FILE *fp, *fpout;
    fp = fopen("rooms.txt","r");
    fpout = fopen("tmp_rooms.txt", "w");
    while(fscanf(fp, "%d %d %d %d %d %d %d %d %s %d", &tmproomID, &tmproomNum, &tmpCap, &tmpcY, &tmpcM, &tmpcD, &tmpcm, &tmpcd, tmptype, &tmpuserID) != EOF){
        if(tmproomNum == roomNum){
            fprintf(fpout, "%d %d %d %d %d %d %d %d %s %d\n", tmproomID, tmproomNum, roomCapacity, startY, startM, startD, endM, endD, tmptype, tmpuserID);
        }else{
            fprintf(fpout, "%d %d %d %d %d %d %d %d %s %d\n", tmproomID, tmproomNum, tmpCap, tmpcY, tmpcM, tmpcD, tmpcm, tmpcd, tmptype, tmpuserID);
        }
    }
    fclose(fp);
    fclose(fpout);
    remove("rooms.txt");
    rename("tmp_rooms.txt", "rooms.txt");
}

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
    system("cls");
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
                system("cls");
                msgInfo("Please enter your USER-ID and PASSWORD.");
                printf("UserID: ");
                scanf("%s", &CurrentUser.id);
                printf("Password: ");
                scanf("%s", &CurrentUser.password);
                if(strcmp(CurrentUser.id, "1") == 0){
                    if(login(CurrentUser.id, CurrentUser.password) == true){
                        isAdmin = 1;
                    }
                }else{
                    if(login(CurrentUser.id, CurrentUser.password) == true){
                        isLogged = 1;
                    }
                }
                if(isAdmin == 1){
                        system("cls");
                        msgInfo("Welcome to Admin Panel");
                        while(true){
                            bookMenu("Modify Room Details", "View Reservations", "View Cancellations", CurrentUser.id);
                            printf("Please enter an option: ");
                            scanf("%d", &aOption1);
                            switch(aOption1){
                                case 1: // modify room details
                                    system("cls");
                                    bookMenu("View Rooms", "Modify Room", "Go Back", CurrentUser.id);
                                    printf("Please select an option: ");
                                    scanf("%d", &aOption1a);
                                    switch(aOption1a){
                                        case 1: // viewRooms()
                                            viewRoom();
                                            msgInfo("Room List");
                                            for(int j = 0; j < roomView[0].availableRooms; j++){
                                                printf("----------------------------------------------\n");
                                                printf("Room No.: %d\n", roomView[j].roomNumber);
                                                printf("Room Type: %s\n", roomView[j].roomType);
                                                printf("Capacity: %d\n", roomView[j].roomCapacity);
                                                printf("Availability: %d/%d/%d - %d/%d/2018\n", roomView[j].checkinDay, roomView[j].checkinMonth, roomView[j].checkinYear, roomView[j].checkoutDay, roomView[j].checkoutMonth);
                                                printf("----------------------------------------------\n");
                                            }
                                            printf("Would you like to continue? (y/n) :");
                                            char cont5;
                                            scanf("%s", &cont5);
                                            if(cont5 == 'y'){
                                                continue;
                                            }
                                        case 2: // modifyRooms()
                                            system("cls");
                                            msgInfo("Enter Room Number to Modify");
                                            printf("Room No.: ");
                                            scanf("%d", &Modify.roomNumber);
                                            printf("Room Capacity: ");
                                            scanf("%d", &Modify.roomCapacity);
                                            printf("Availability Status: \n");
                                            printf("----------------------------------------------\n");
                                            printf("Start Year: ");
                                            scanf("%d", &Modify.checkinYear);
                                            printf("Start Month: ");
                                            scanf("%d", &Modify.checkinMonth);
                                            printf("Start Day: ");
                                            scanf("%d", &Modify.checkinDay);
                                            printf("End Month: ");
                                            scanf("%d", &Modify.checkoutMonth);
                                            printf("End Day: ");
                                            scanf("%d", &Modify.checkoutDay);
                                            editRoom(Modify.roomNumber, Modify.roomCapacity, Modify.checkinYear, Modify.checkinMonth, Modify.checkinDay, Modify.checkoutMonth, Modify.checkoutDay);
                                            msgInfo("Room Successfully Edited");
                                            printf("Would you like to continue? (y/n) :");
                                            char cont6;
                                            scanf("%s", &cont6);
                                            if(cont5 == 'y'){
                                                continue;
                                            }
                                        case 3: // go back
                                            break;
                                    }
                                case 2: // view reservation
                                    system("cls");
                                    bookMenu("View Reservation", "Search Reservation", "Go Back", CurrentUser.id);
                                    printf("Please select an option: ");
                                    scanf("%d", &aOption2);
                                    switch(aOption2){
                                        case 1: // view reservation
                                            viewReservations();
                                            msgInfo("Reservation List");
                                            for(int j = 0; j < resView[0].availableRooms; j++){
                                                printf("----------------------------------------------\n");
                                                printf("Room No.: %d\n", resView[j].roomNumber);
                                                printf("Name: %s\n", users[j].name);
                                                printf("Age: %d\n", users[j].age);
                                                printf("Gender: %s\n", users[j].gender);
                                                printf("Check-In Date: %d/%d/%d\n", resView[j].checkinDay, resView[j].checkinMonth, resView[j].checkinYear);
                                                printf("Check-Out Date: %d/%d\n", resView[j].checkoutDay, resView[j].checkoutMonth);
                                                printf("----------------------------------------------\n");
                                            }
                                            printf("Would you like to continue? (y/n) :");
                                            char cont7;
                                            scanf("%s", &cont7);
                                            if(cont7 == 'y'){
                                                continue;
                                            }
                                        case 2: // search reservation
                                            msgInfo("Search Reservations");
                                            printf("Enter room number: ");
                                            scanf("%d", &Booked.roomNumber);
                                            searchReservations(Booked.roomNumber);   
                                            printf("----------------------------------------------\n");
                                            printf("Room No.: %d\n", searchRes[0].roomNumber);
                                            printf("Name: %s\n", users[0].name);
                                            printf("Age: %d\n", users[0].age);
                                            printf("Gender: %s\n", users[0].gender);
                                            printf("Check-In Date: %d/%d/%d\n", searchRes[0].checkinDay, searchRes[0].checkinMonth, searchRes[0].checkinYear);
                                            printf("Check-Out Date: %d/%d\n", searchRes[0].checkoutDay, searchRes[0].checkoutMonth);
                                            printf("----------------------------------------------\n");
                                            printf("Would you like to continue? (y/n) :");
                                            char cont8;
                                            scanf("%s", &cont8);
                                            if(cont8 == 'y'){
                                                continue;
                                            }
                                        case 3: // go back
                                            break;
                                    }
                                case 3: // view cancellations
                                    msgInfo("View Cancellations");
                                    viewCancellations();
                                    for(int j = 0; j < cancellations[0].availableRooms; j++){
                                        printf("----------------------------------------------\n");
                                        printf("Room No.: %d\n", cancellations[j].roomNumber);
                                        printf("Name: %s\n", users[j].name);
                                        printf("Age: %d\n", users[j].age);
                                        printf("Gender: %s\n", users[j].gender);
                                        printf("Check-In Date: %d/%d/%d\n", cancellations[j].checkinDay, cancellations[j].checkinMonth, cancellations[j].checkinYear);
                                        printf("Check-Out Date: %d/%d\n", cancellations[j].checkoutDay, cancellations[j].checkoutMonth);
                                        printf("Reason: %s\n", cancellations[j].reason);
                                        printf("----------------------------------------------\n");
                                    }
                                    printf("Would you like to continue? (y/n) :");
                                    char cont9;
                                    scanf("%s", &cont9);
                                    if(cont9 == 'y'){
                                        break;
                                    }
                                    
                            }
                        }
                    }else if(isLogged == 1){
                    system("cls");
                    while(true){
                        system("cls");
                        bookMenu("Bookings", "Modify Booking", "View Status", CurrentUser.id);
                        printf("Please enter an option: ");
                        scanf("%d", &userInput2);
                        // system("cls");
                        switch(userInput2){
                            case 1:
                                system("cls");
                                bookMenu("Availability", "Reservation", "Go Back", CurrentUser.id);
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
                                bookMenu("Edit Booking", "Cancellation", "Go Back", CurrentUser.id);
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
                                            continue;
                                        }
                                    case 2:
                                        msgInfo("Room Reservation Cancellation");
                                        printf("Enter room number: ");
                                        scanf("%d", &Cancel.roomNumber);
                                        printf("Reason: ");
                                        scanf("%s", &Cancel.reason);
                                        cancelRoom(Cancel.roomNumber, Cancel.reason);
                                        msgInfo("Reservation Successfully Cancelled");
                                    case 3:
                                        break;
                                }
                            case 3:
                                system("cls");
                                bookMenu("Reservations", "Go Back", " ", CurrentUser.id);
                                printf("Please select your option: ");
                                scanf("%d", &userInput5);
                                switch(userInput5){
                                    case 1:
                                        system("cls");        
                                        msgInfo("View Reservations");
                                        printf("Enter user-ID: ");
                                        scanf("%d", &CurrentUser.userid);
                                        reservations(CurrentUser.userid);
                                        if(Reservation[0].reservations == 0){
                                            msgInfo("You have no reservations.");
                                        }
                                        for(int k = 0; k < Reservation[0].reservations; k++){
                                            printf("Room Number: %d\n", Reservation[k].roomNumber);
                                            printf("Check-In Date: %d/%d/%d\n", Reservation[k].checkinDay, Reservation[k].checkinMonth, Reservation[k].checkinYear);
                                            printf("Check-Out Date: %d/%d\n", Reservation[k].checkoutMonth, Reservation[k].checkoutDay);
                                            printf("----------------------------------------------\n");
                                        }
                                        printf("Would you like to continue? (y/n):");
                                        char cont4;
                                        scanf("%s", &cont4);
                                        if(cont4 == 'y'){
                                            continue;
                                        }
                                    case 2:
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
        // break;
    }
    return 0;
}