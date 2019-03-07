/*
By:Clayton Provan
Assignement 3 part 2.2
march 4th
*/

#include "stdio.h"
#include "sys/timeb.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const int maxString = 1000;

void createTable(char*pattern,int shiftTable[],int shiftSize);

int main(){
  FILE *fp;
  char *searchStr  = malloc(sizeof(char)*maxString);
  char *str;

  struct timeb t_start, t_end;
  //256 to represent ascii tables although could be smaller because we are only using A-Z and a-z
  int table[512];
  int timeElapsed;
  int i=0;
  int j=1;
  int k=0;
  int len = 0;
  int count =0;
  int transfer;
  char c;


  fp=fopen("data_5.txt","r");
  str =calloc(1000000,sizeof(char));
  //read in all characters
  while((c = fgetc(fp)) != EOF){
    str[i] = c;
    i++;
    if(i == 1000000*j){
      j++;
      str =realloc(str,sizeof(char)*1000000*j);
    }
  }


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

  createTable(searchStr,table,512);
  j=len-1;

  while(j<i){
    k=0;

    while(k<len && (searchStr[len-1-k]==str[j-k])){
      k++;
    }

    if(k==len){
        count++;
        j++;
    }else{
      transfer = str[j];
      //used when unicode values appear in text and will create negative index values.
      if(transfer>512 || transfer<0){
        j=j+len;
      }else{
        j=j+table[transfer];
      }
    }

  }


  ftime(&t_end);
  timeElapsed = (int)(1000.0*(t_end.time - t_start.time) + (t_end.millitm - t_start.millitm));
  printf("%s appears %d times\n",searchStr,count);
  printf("Time Elapsed %d milliseconds\n",timeElapsed);


  free(searchStr);
  free(str);
  fclose(fp);
  return 1;
}

void createTable(char*pattern,int shiftTable[],int shiftSize){
  int len=0;
  int i=0;
  int temp;

  len = strlen(pattern);
  //initlize all to maxshift size
  for(i=0;i<shiftSize;i++){
    shiftTable[i] = len;
  }

  //find last occurence of character and set shiftsize;
  for(i=0;i<len-1; i++){
    temp = pattern[i];
    shiftTable[temp] = len-i-1;
  }

}
