/*
By:Clayton Provan
Assignement 3 part 2.1
march 4th
*/

#include "stdio.h"
#include "sys/timeb.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const int maxString = 1000;


int main(){
  FILE *fp;
  char *tempStr = malloc(sizeof(char)*maxString);
  char *searchStr  = malloc(sizeof(char)*maxString);
  char **str;
  struct timeb t_start, t_end;
  int timeElapsed;
  int i=0;
  int j=0;
  int k=0;
  int t=0;
  int len =0;
  int wordLen=0;
  int count =0;


  fp=fopen("data_5.txt","r");
  str =calloc(1000000,sizeof(char*));

  while( fscanf(fp, "%s", tempStr) != EOF )
  {
    str[i] = calloc(1,sizeof(char)*strlen(tempStr)+1);
    strcpy(str[i],tempStr);
    i++;
  }
  printf("%d\n",i );
  printf("enter pattern to find\n");
  fgets(searchStr, sizeof(char)*1001, stdin);
  searchStr[strcspn(searchStr, "\n")] = 0;

//checks for valid input from user
  len = strlen(searchStr);
  for(j=0;j<len;j++){
    if(isalpha(searchStr[j]) == 0){
      printf(":%c:\n",searchStr[j] );
      printf("Invalid entry, can only contain the 52 upper and lower case letters only \n");
      return 1;
    }
  }

  ftime(&t_start);

  //since no spaces can be included we only need to compare each string
  for(j=0;j<i;j++){
    k=0;
    t=0;
    strcpy(tempStr,str[j]);
    wordLen = strlen(str[j])+1;
    //goes through all letters in string and sees if a match occurs
    //by checking if the searched string matched the letters in the temp string the correct number of times
    //then resets to check if desired string can be found in the temp string again.
    //if we encounter a comparision that is not true we reset and start searchin for 0th index of search string again.
    //continually incrementing the index of compared (temporary string) untill we reach the end
    while(k<wordLen){
      if(searchStr[t] == tempStr[k] ){
        t++;
        if(t==len){
          count++;
          t=0;
        }
      }else{
        t=0;
        //if next index show it can be within word we dont increment;
        if(searchStr[t] == tempStr[k]) k--;
      }
      k++;
    }
  }



  ftime(&t_end);
  timeElapsed = (int)(1000.0*(t_end.time - t_start.time) + (t_end.millitm - t_start.millitm));
  printf("%s appears %d times\n",searchStr,count);
  printf("Time Elapsed %d milliseconds\n",timeElapsed);


  for(j=0;j<i;j++){
    free(str[j]);
  }
  free(str);
  free(tempStr);
  fclose(fp);

  return 1;
}
