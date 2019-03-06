/*
brute force algorithm based on the definition of inversion, which checks every
pair of (A[i], A[j]) for i < j.

*/

#include "stdio.h"
#include "sys/timeb.h"
int bruteForceInversions(int array[],int length);


int main(){
  FILE *fp;
  struct timeb t_start, t_end;
  int in,count,i=0;
  int timeElapsed;
  int array1[50000];

  fp=fopen("data_1.txt","r");
  while(i<50000 && (in = fscanf(fp,"%d", &array1[i++]))==1);


  ftime(&t_start);
  count = bruteForceInversions(array1,50000);
  ftime(&t_end);
  timeElapsed = (int)(1000.0*(t_end.time - t_start.time) + (t_end.millitm - t_start.millitm));

  printf("brute force:%d , took %d milliseconds\n",count,timeElapsed);

  return 1;
}

int bruteForceInversions(int array[],int length){
  int i,j,count;
  //counts number of inversion exsit
  count =0;

  //iterate through array to check if index at i is greater than j
  for(j=0; j<length;j++){
    for(i=0; i<j;i++){
      if(array[i] > array[j]){
        count++;
      }
    }
  }

  return count;
}
