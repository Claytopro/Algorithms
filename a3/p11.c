/*
By:Clayton Provan
Assignement 3
march 4th
*/

#include "stdio.h"
#include "sys/timeb.h"
#include <stdlib.h>
#include <string.h>

const int maxString = 1000;
int isAnagram(char *toFind, char *toCompare);

int main(){
  FILE *fp;
  char *tempStr = malloc(sizeof(char)*maxString);
  char *str[30000];
  struct timeb t_start, t_end;
  int timeElapsed;
  int i=0;
  int count =0;


  fp=fopen("data_4.txt","r");

  while( fscanf(fp, "%s", tempStr) != EOF )
  {

    str[i] = malloc(sizeof(char)*strlen(tempStr)+1);
    strcpy(str[i],tempStr);
    i++;
  }
  ftime(&t_start);
  printf("enter number for anagram to find\n");
  fgets(tempStr, sizeof(char)*1001, stdin);
  tempStr[strcspn(tempStr, "\n")] = 0;

  for(i=0;i<30000;i++){
    count += isAnagram(tempStr,str[i]);
  }
  ftime(&t_end);
  timeElapsed = (int)(1000.0*(t_end.time - t_start.time) + (t_end.millitm - t_start.millitm));

  printf("there are %d anagrams of %s\n",count,tempStr);

  printf("Time Elapsed %d milliseconds\n",timeElapsed);

  fclose(fp);
  return 1;
}

int isAnagram(char *toFind, char *toCompare){
  int charCount1[256] = {0};
  int charCount2[256] = {0};
  int k,j;

  //ignores exact copies of the desired string to find
  if(strcmp(toFind,toCompare)==0){

    return 0;
  }

  int size1 = strlen(toCompare);
  int size2 = strlen(toFind);
  //if the string are not the same length then they cant be anagrams of one another.
  if(size1 != size2) return 0;
  //counts all characters
  for (size_t i = 0; i < size2; i++) {
    k=toFind[i];
    j =toCompare[i];
    charCount1[k]++;
    charCount2[j]++;
  }

  for (size_t i = 0; i < 256; i++) {
    if(charCount1[i] != charCount2[i]) return 0;
  }

  return 1;
}
