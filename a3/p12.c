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
int isAnagrm(char *toFind, char *toCompare);

void sortString(char *str,int l,int r);
void merge(char *str, int l, int m, int r);

int p12(){
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
  //gets user input and removes newline at end
  printf("enter number for anagram to find\n");
  fgets(tempStr, sizeof(char)*1001, stdin);
  tempStr[strcspn(tempStr, "\n")] = 0;


  ftime(&t_start);
  sortString(tempStr,0,strlen(tempStr)-1);
  for(i=0;i<30000;i++){
    sortString(str[i],0,strlen(str[i])-1);
  }
  ftime(&t_end);
  timeElapsed = (int)(1000.0*(t_end.time - t_start.time) + (t_end.millitm - t_start.millitm));

  printf("Sorting Time Elapsed %d milliseconds\n",timeElapsed);

  ftime(&t_start);
  for(i=0;i<30000;i++){
    count += isAnagrm(tempStr,str[i]);
  }
  ftime(&t_end);
  timeElapsed = (int)(1000.0*(t_end.time - t_start.time) + (t_end.millitm - t_start.millitm));

  printf("Searching Time Elapsed %d milliseconds\n",timeElapsed);

  printf("there are %d anagrams\n",count);

  fclose(fp);
  return 1;
}

//if strings match then they are anagrams, because we sort strings first then search this will make it count additionally if the string is part of
//list so cat will be anagram of cat
int isAnagrm(char *toFind, char *toCompare){
  if(strcmp(toFind,toCompare) == 0) return 1;
  return 0;
}

void sortString(char str[],int l,int r){
  int middle;

  if(l<r){
    middle = l + (r-l)/2;
    sortString(str,l,middle);
    sortString(str,middle+1,r);
    merge(str,l,middle,r);
  }

}

void merge(char arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l +1;
    int n2 =  r - m  ;

    /* create temp arrays */
    char L[n1+1];
    char R[n2+1];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];


    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;

        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

}
