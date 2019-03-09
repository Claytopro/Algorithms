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


void createSuffixtable(char*pattern,int shiftTable[],int shiftSize);
void createTable(char*pattern,int shiftTable[],int shiftSize);
int max (int x, int y);

int p23(){
  FILE *fp;
  char *searchStr  = malloc(sizeof(char)*1000);
  char *str;

  struct timeb t_start, t_end;
  //256 to represent ascii tables although could be smaller because we are only using A-Z and a-z
  int table[512];
  int tableGood[512] ={0};
  int timeElapsed;
  int i=0;
  int j=1;
  int k=0;
  int len = 0;
  int count =0;
  int transfer=0;
  char c;
  int shiftCount=0;


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
      printf("Invalid entry, can only contain the 52 upper and lower case letters only \n");
      return 1;
    }
  }

  ftime(&t_start);

  createTable(searchStr,table,512);
  createSuffixtable(searchStr,tableGood,512);

  j=len-1;
  k=len-1;

  while(j<i){

    k=len-1;
    while(k>=0 && searchStr[k]==str[j]){
          k--;
          j--;
      }


    if(k<0){
      count++;
      j = j+ tableGood[0]+1;
      shiftCount++;
    }else{
      transfer = str[j];
      if(transfer<0 || transfer>511) transfer =0;
      shiftCount++;
      j += max(tableGood[k],table[transfer]);
    }


  }


  ftime(&t_end);

  timeElapsed = (int)(1000.0*(t_end.time - t_start.time) + (t_end.millitm - t_start.millitm));
  printf("%s appears %d times\n",searchStr,count);
  printf("Time Elapsed %d milliseconds\n",timeElapsed);
  printf("there are %d shifts \n",shiftCount );


  free(searchStr);
  free(str);
  fclose(fp);
  return 1;
}
//creates table for bad character rule same as hoops
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


void createSuffixtable(char*pattern,int shiftTable[],int shiftSize){
    int patternLen;
    int i=0;
    int match,prefex,j;

    patternLen = strlen(pattern);
    prefex = patternLen-1;

    //find longest possible matches to any prefixes in the pattern
    for(i=patternLen;i>=0;i--){
     match =1;
      for(j=0;j<(patternLen-i+1);j++){
        if(pattern[j] != pattern[i+j]){
          match =0;
        }
      }
      if(match ==1){
        prefex = i+1;
      }
      shiftTable[i] = prefex + patternLen -1 -i;
    }

    //find section of pattern input that is unique. take smallest value because it
    // may occur in middle of string or elsewhere and the smallest will tell us how far next possible match may be
    for(i=0;i<patternLen-1;i++){

      j=0;
      while(pattern[i-j]==pattern[patternLen-1-j] && j<i){
        j++;
      }


      if(pattern[i-j] != pattern[patternLen-1-j]){
        shiftTable[patternLen-1-j] = patternLen-1-i+j;
      }
    }

}

//simple helper function for boyermoor algorithm
int max (int x, int y){
	if (x > y){
		return x;
	}
	else{
		return y;
	}
}
