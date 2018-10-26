#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
}

int main(void) {
        userReg(1, "Foo", "Bar");
        userReg(2,"Miss", "Foo");
        return 0;
    
}