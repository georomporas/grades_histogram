/*
*   Author: Georgios Romporas    
*   Created for the IP class 2023 in Nov 16 2023 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
const unsigned int YLEN = 40;

int main(){
  int grade[11] = { 0 }; // We want the grades from grade[1] up to and including grade[10]

  /******** Get the grades from the proodos.txt file ********/
  /* IMPORTANT: Make sure that the proodos.txt file is in the working directory
     of the running .c program, otherwise the code won't work! */

  FILE *proodos;
  proodos = fopen("randgrade.txt", "r");
  if(proodos == NULL){
    printf("ERROR, CAN'T LOCATE FILE\n");
    return 1;
  }

  

  char *string;
  size_t stringLen = 64;
  string = calloc(64, sizeof(char)); 

  if(string == NULL){
    printf("Error allocating memory!\n");
    return 1;
  }

  int ch;
  int idx=0; 
  while( (ch = fgetc(proodos)) != EOF ){
      
    if(ch == 10){ // ch == '\n'
      string[idx] = '\0';

      double currGrade = 0.0;
      int entered = -1;
      int mul = 1;

      for(int i =idx-1; i>=0; i--){
        
        if(string[i]>=48 && string[i]<=57){
          entered = 1;
          currGrade += (double)((string[i]-48)*mul);
          mul*=10;
        }else if(string[i]==46 && entered==1){
          currGrade /=(double)mul;
          mul = 1;
        }else if(string[i]==32 && entered==1){
          idx = 0;
          break;
        }
      }
      
      int val = lroundf(currGrade);
      //printf("VAL:%d\n", val);
      if(val>=1 && val<=10){
        grade[val]++;
      }
      


      idx = 0;
      free(string);
      stringLen = 64;
      string = calloc(64, sizeof(char)); 

    }else{
      string[idx]= (char)ch;
      idx++;
    }

    if(idx>=64){         // --- Out of bounds --- //
      stringLen*=2;
      string = realloc(string, stringLen * sizeof(char));
      if(string == NULL){
        printf("Error allocating memory!\n");
      }
    }
    
  }

  fclose(proodos);
  /******** We can close the file since it has no further use ********/

  int sum = 0;
  for(int i=1; i<=10; i++){
    sum+= grade[i];
    //printf("%d\n" , grade[i]);
  }
    
  for(int i = 1; i<=10; i++){
    grade[i] = lroundf(100.0*grade[i]/sum); 
  }

  for(int j=YLEN; j>=1; j--){
    printf("\033[1;32m%2d%%\033[1;0m║", j);

    for(int i =1; i<=10; i++){
        
      if(i==1){
        printf(" ");
      }

      printf("%s", (grade[i]>=j)? "\033[1;34m███\033[1;0m" : "   ");
      printf(" ");
    }
      
    printf("\n");
  }
  printf("   ╚═════════════════════════════════════════\n");
  printf("\033[1;31m      1   2   3   4   5   6   7   8   9   10 \n\033[1;0m");

  return 0;
}