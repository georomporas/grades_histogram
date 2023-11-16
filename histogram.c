/*
*   Author: Georgios Romporas    
*   Created for the IP class 2023 in Nov 16 2023 
*/

#include <stdio.h>
#include <math.h>
const unsigned int YLEN = 25;

int main(){
  int grade[11] = { 0 }; // We want the grades from grade[1] up to and including grade[10]

  /******** Get the grades from the proodos.txt file ********/
  /* IMPORTANT: Make sure that the proodos.txt file is in the working directory
     of the running .c program, otherwise the code won't work! */

  FILE *proodos;
  proodos = fopen("proodos.txt", "r");
  if(proodos != NULL){
    int ch;
    int cnt=0; 
    while( (ch = fgetc(proodos)) != EOF ){
      
      cnt++;
      if(cnt>=7){
        grade[ ch-48 ]++;
      }

      if(ch == 10){ // ch == '\n'
        cnt = 0;
      }

    }
    grade[10] = grade[0]; 
    grade[1] /= 2; // We wrongly counted the 1s when the grade was 10

    fclose(proodos);
    /******** We can close the file since it has no further use ********/

    int sum = 0;
    for(int i=1; i<=10; i++){
      sum+= grade[i];
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

  }else{  
    printf("ERROR, CAN'T LOCATE FILE\n");
  }

  return 0;
}